#include <gtk/gtk.h>

#include "../defines.h"
#include "../util.h"
#include "../generated_headers/android_view_ViewTreeObserver.h"

static void on_global_layout_callback(GdkFrameClock *clock, jobject view_tree_observer)
{
	JNIEnv *env = get_jni_env();
	(*env)->CallVoidMethod(env, view_tree_observer, handle_cache.view_tree_observer.dispatchOnGlobalLayout);
	if ((*env)->ExceptionCheck(env)) {
		(*env)->ExceptionDescribe(env);
		(*env)->ExceptionClear(env);
	}
}

static void on_pre_draw_callback(GdkFrameClock *clock, jobject view_tree_observer)
{
	JNIEnv *env = get_jni_env();
	(*env)->CallBooleanMethod(env, view_tree_observer, handle_cache.view_tree_observer.dispatchOnPreDraw);
	if ((*env)->ExceptionCheck(env)) {
		(*env)->ExceptionDescribe(env);
		(*env)->ExceptionClear(env);
	}
}

extern GtkWidget *window;

void _gdb_force_java_stack_trace(void);

JNIEXPORT void JNICALL Java_android_view_ViewTreeObserver_native_1set_1have_1global_1layout_1listeners(JNIEnv *env, jobject this, jboolean have_listeners)
{
	GtkWidget *window = _PTR(_GET_LONG_FIELD(this, "window"));

	if (!window) {
		fprintf(stderr, "Java_android_view_ViewTreeObserver_native_1set_1have_1global_1layout_1listeners: no window\n");
		return;
	}

	gulong signal_handle = _GET_LONG_FIELD(this, "onGlobalLayout_signal_handle");
	GdkFrameClock *clock = gtk_widget_get_frame_clock(window);

	if (have_listeners && !signal_handle) {
		/* GTKs own handler is always the first, so our handler gets called after all widgets have been measured and allocated */
		signal_handle = g_signal_connect(G_OBJECT(clock), "layout", G_CALLBACK(on_global_layout_callback), _REF(this)); // FIXME: cleanup callback for _UNREF
		_SET_LONG_FIELD(this, "onGlobalLayout_signal_handle", signal_handle);
	} else if (!have_listeners && signal_handle) {
		g_signal_handler_disconnect(G_OBJECT(clock), signal_handle);
		_SET_LONG_FIELD(this, "onGlobalLayout_signal_handle", 0);
	} else {
		fprintf(stderr, "Java_android_view_ViewTreeObserver_native_1set_1have_1global_1layout_1listeners: invalid state: have_listeners: %d, signal_handle: 0x%016w64x\n", have_listeners, signal_handle);
		exit(1);
	}
}

JNIEXPORT void JNICALL Java_android_view_ViewTreeObserver_native_1set_1have_1predraw_1listeners(JNIEnv *env, jobject this, jboolean have_listeners)
{
	GtkWidget *window = _PTR(_GET_LONG_FIELD(this, "window"));

	if (!window) {
		fprintf(stderr, "Java_android_view_ViewTreeObserver_native_1set_1have_1predraw_1listeners: no window\n");
		return;
	}

	gulong signal_handle = _GET_LONG_FIELD(this, "onPreDraw_signal_handle");
	GdkFrameClock *clock = gtk_widget_get_frame_clock(window);

	if (have_listeners && !signal_handle) {
		/* Unlike AOSP, our hook gets invoked after all widgets have been drawn. */
		/* Switching to ::layout would fix the timing, but we would miss frames where no layout was requested. */
		/* TODO: Hook into the DecorView snapshot function to get in before widget drawing. */
		signal_handle = g_signal_connect(G_OBJECT(clock), "paint", G_CALLBACK(on_pre_draw_callback), _REF(this)); // FIXME: cleanup callback for _UNREF
		_SET_LONG_FIELD(this, "onPreDraw_signal_handle", signal_handle);
	} else if (!have_listeners && signal_handle) {
		g_signal_handler_disconnect(G_OBJECT(clock), signal_handle);
		_SET_LONG_FIELD(this, "onPreDraw_signal_handle", 0);
	} else {
		fprintf(stderr, "Java_android_view_ViewTreeObserver_native_1set_1have_1predraw_1listeners: invalid state: have_listeners: %d, signal_handle: 0x%016w64x\n", have_listeners, signal_handle);
		exit(1);
	}
}
