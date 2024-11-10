#include <sys/poll.h>
#include <wayland-server.h>
#include <GL/gl.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <gtk/gtk.h>
#include <gdk/wayland/gdkwayland.h>

#include "../api-impl-jni/defines.h"

static EGLDisplay egl_display_gtk = NULL;
static GdkGLContext *gl_context_gtk = NULL;
static struct wl_event_loop *event_loop = NULL;
static GMutex mutex;
static PFNEGLQUERYWAYLANDBUFFERWL eglQueryWaylandBufferWL = NULL;
static PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glEGLImageTargetTexture2DOES = NULL;

/* runs on main thread */
static gboolean delete_texture(void *data) {
	GLuint texture_id = (uintptr_t)data;
	gdk_gl_context_make_current(gl_context_gtk);
	glDeleteTextures(1, &texture_id);
	return G_SOURCE_REMOVE;
}

struct _BufferData {
	GObject parent;
	gboolean destroyed;
	GtkPicture *picture;
	struct wl_resource *wl_buffer;
	GdkGLTextureBuilder *texture_builder;
};
G_DECLARE_FINAL_TYPE(BufferData, buffer_data, ATL, BUFFER_DATA, GObject);
static void buffer_data_dispose(GObject *g_object)
{
	BufferData *buffer = ATL_BUFFER_DATA(g_object);
	if (buffer->texture_builder) {
		GLuint texture_id = gdk_gl_texture_builder_get_id(buffer->texture_builder);
		g_idle_add(delete_texture, _PTR(texture_id));
		g_object_unref(buffer->texture_builder);
	}
	g_object_unref(buffer->picture);
}
static void buffer_data_class_init(BufferDataClass *cls)
{
	cls->parent_class.dispose = buffer_data_dispose;
}
static void buffer_data_init(BufferData *self) {}
G_DEFINE_TYPE(BufferData, buffer_data, G_TYPE_OBJECT)

struct surface {
	struct wl_resource *wl_surface;
	GtkPicture *picture;
	struct wl_resource *frame_callback;
	BufferData *buffers[3];
};

/* runs on main thread */
static void destroy_texture(void *data) {
	BufferData *buffer = ATL_BUFFER_DATA(data);
	g_mutex_lock(&mutex);
	if (!buffer->destroyed) {
		wl_buffer_send_release(buffer->wl_buffer);
	}
	g_mutex_unlock(&mutex);
	g_object_unref(buffer);
}

/* runs on main thread */
static gboolean render_texture(void *data) {
	BufferData *buffer = ATL_BUFFER_DATA(data);
	if (!buffer->texture_builder) {
		g_mutex_lock(&mutex);
		if (buffer->destroyed) {
			g_mutex_unlock(&mutex);
			g_object_unref(buffer);
			return G_SOURCE_REMOVE;
		}
		EGLImage image = eglCreateImage(egl_display_gtk, EGL_NO_CONTEXT, EGL_WAYLAND_BUFFER_WL, buffer->wl_buffer, (EGLAttrib[]){EGL_NONE});
		GLuint texture_id;
		int width, height;
		eglQueryWaylandBufferWL(egl_display_gtk, buffer->wl_buffer, EGL_WIDTH, &width);
		eglQueryWaylandBufferWL(egl_display_gtk, buffer->wl_buffer, EGL_HEIGHT, &height);
		gdk_gl_context_make_current(gl_context_gtk);
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, image);
		glBindTexture(GL_TEXTURE_2D, 0);
		eglDestroyImage(egl_display_gtk, image);
		g_mutex_unlock(&mutex);
		buffer->texture_builder = gdk_gl_texture_builder_new();
		gdk_gl_texture_builder_set_context(buffer->texture_builder, gl_context_gtk);
		gdk_gl_texture_builder_set_id(buffer->texture_builder, texture_id);
		gdk_gl_texture_builder_set_format(buffer->texture_builder, GDK_MEMORY_R8G8B8A8_PREMULTIPLIED);
		gdk_gl_texture_builder_set_width(buffer->texture_builder, width);
		gdk_gl_texture_builder_set_height(buffer->texture_builder, height);
	}

	GdkTexture *texture = gdk_gl_texture_builder_build(buffer->texture_builder, destroy_texture, buffer);

	gtk_picture_set_paintable(buffer->picture, GDK_PAINTABLE(texture));
	g_object_unref(texture);

	return G_SOURCE_REMOVE;
}

static void surface_attach(struct wl_client *client, struct wl_resource *resource, struct wl_resource *wl_buffer, int32_t x, int32_t y)
{
	struct surface *surface = wl_resource_get_user_data(resource);
	// Order buffer cache by least recently used.
	BufferData *buffer = surface->buffers[0];
	if (buffer && buffer->wl_buffer == wl_buffer)
		return;
	buffer = surface->buffers[1];
	surface->buffers[1] = surface->buffers[0];
	surface->buffers[0] = buffer;
	if (buffer && buffer->wl_buffer == wl_buffer)
		return;
	buffer = surface->buffers[2];
	surface->buffers[2] = surface->buffers[0];
	surface->buffers[0] = buffer;
	if (buffer && buffer->wl_buffer == wl_buffer)
		return;
	// If the buffer is not in the cache, create it and drop the oldest one.
	if (buffer)
		g_object_unref(buffer);
	buffer = g_object_new(buffer_data_get_type(), NULL);
	buffer->wl_buffer = wl_buffer;
	buffer->picture = g_object_ref(surface->picture);
	surface->buffers[0] = buffer;
}

static void surface_frame(struct wl_client *client, struct wl_resource *resource, uint32_t callback)
{
	struct surface *surface = wl_resource_get_user_data(resource);
	surface->frame_callback = wl_resource_create(client, &wl_callback_interface, 1, callback);
}

static void surface_damage(struct wl_client *client, struct wl_resource *resource, int32_t x, int32_t y, int32_t width, int32_t height)
{
}

static int frame_timer(void *data)
{
	struct wl_resource *frame_callback = data;
	wl_callback_send_done(frame_callback, g_get_monotonic_time()/1000);
	wl_resource_destroy(frame_callback);
	return 0;
}

static void surface_commit(struct wl_client *client, struct wl_resource *resource)
{
	struct surface *surface = wl_resource_get_user_data(resource);
	g_idle_add(render_texture, g_object_ref(surface->buffers[0]));
	struct wl_event_source *timer = wl_event_loop_add_timer(event_loop, frame_timer, surface->frame_callback);
	wl_event_source_timer_update(timer, 1000/60);
}

static void surface_destroy(struct wl_client *client, struct wl_resource *resource) {
	struct surface *surface = wl_resource_get_user_data(resource);
	for (int i = 0; i < 3; i++) if (surface->buffers[i]) {
		surface->buffers[i]->destroyed = TRUE;
		g_object_unref(surface->buffers[i]);
	}
	g_object_unref(surface->picture);
	wl_resource_destroy(surface->wl_surface);
	g_free(surface);
}

/* we abuse this method to set lower 32 bits of the GtkPicture pointer */
static void surface_set_buffer_scale(struct wl_client *client, struct wl_resource *resource, int32_t scale)
{
	struct surface *surface = wl_resource_get_user_data(resource);
	surface->picture = _PTR((((uint64_t)(uintptr_t)surface->picture) & 0xffffffff00000000L) | ((uintptr_t)(uint32_t)scale));
}

/* we abuse this method to set higher 32 bits of the GtkPicture pointer */
static void surface_set_buffer_transform(struct wl_client *client, struct wl_resource *resource, int32_t transform)
{
	struct surface *surface = wl_resource_get_user_data(resource);
	surface->picture = _PTR((((uint64_t)(uintptr_t)surface->picture) & 0x00000000ffffffffL) | ((uintptr_t)(uint32_t)transform)<<32);
}

static struct wl_surface_interface surface_implementation = {
	.attach = surface_attach,
	.frame = surface_frame,
	.damage = surface_damage,
	.commit = surface_commit,
	.destroy = surface_destroy,
	.set_buffer_scale = surface_set_buffer_scale,
	.set_buffer_transform = surface_set_buffer_transform,
};

static void compositor_create_surface(struct wl_client *client, struct wl_resource *resource, uint32_t id)
{
	struct wl_resource *wl_surface = wl_resource_create(client, &wl_surface_interface, 3, id);
	struct surface *surface = g_new0(struct surface, 1);
	wl_resource_set_implementation(wl_surface, &surface_implementation, surface, NULL);
	surface->wl_surface = wl_surface;
}

static struct wl_compositor_interface compositor_implementation = {
	.create_surface = compositor_create_surface,
};

static void compositor_bind(struct wl_client *client, void *data, uint32_t version, uint32_t id) {
	struct wl_resource *resource = wl_resource_create(client, &wl_compositor_interface, 1, id);
	wl_resource_set_implementation(resource, &compositor_implementation, NULL, NULL);
}

static gpointer wayland_server_thread(gpointer user_data)
{
	struct wl_display *wl_display_server = user_data;
	struct pollfd pollfd = {
		.fd = wl_event_loop_get_fd(event_loop),
		.events = POLLIN | POLLOUT,
	};
	for (;;) {
		poll(&pollfd, 1, -1);
		g_mutex_lock(&mutex);
		wl_event_loop_dispatch(event_loop, 0);
		wl_display_flush_clients(wl_display_server);
		g_mutex_unlock(&mutex);
	}
	return 0;	
}

extern GtkWindow *window;

struct wl_display *wayland_server_start()
{
	GdkDisplay *gdk_display = gtk_root_get_display(GTK_ROOT(window));
	struct wl_display *wl_display_gtk = gdk_wayland_display_get_wl_display(gdk_display);
	egl_display_gtk = eglGetPlatformDisplay(EGL_PLATFORM_WAYLAND_KHR, wl_display_gtk, NULL);
	gl_context_gtk = gdk_surface_create_gl_context(gtk_native_get_surface(GTK_NATIVE(window)), NULL);

	struct wl_display *wl_display_server = wl_display_create();
	char tmpname[] = "/tmp/tmpdir.XXXXXX\0socket";
	int tmplen = strlen(tmpname);
	mkdtemp(tmpname);
	tmpname[tmplen] = '/';
	wl_display_add_socket(wl_display_server, tmpname);
	struct wl_display *wl_display_client = wl_display_connect(tmpname);
	tmpname[tmplen] = '\0';
	rmdir(tmpname);

	wl_global_create(wl_display_server, &wl_compositor_interface, 3, NULL, &compositor_bind);
	event_loop = wl_display_get_event_loop(wl_display_server);
	g_mutex_init(&mutex);
	PFNEGLBINDWAYLANDDISPLAYWL eglBindWaylandDisplayWL = (PFNEGLBINDWAYLANDDISPLAYWL)eglGetProcAddress("eglBindWaylandDisplayWL");
	eglQueryWaylandBufferWL = (PFNEGLQUERYWAYLANDBUFFERWL)eglGetProcAddress("eglQueryWaylandBufferWL");
	glEGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
	eglBindWaylandDisplayWL(egl_display_gtk, wl_display_server);
	g_thread_new("wayland-server", wayland_server_thread, wl_display_server);

	return wl_display_client;
}
