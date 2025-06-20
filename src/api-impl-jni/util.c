#include <stdint.h>
#include <dlfcn.h>
#include <pthread.h>

#include <gtk/gtk.h>

#include "util.h"
#include "src/api-impl-jni/defines.h"

struct handle_cache handle_cache = {0};

const char * attribute_set_get_string(JNIEnv *env, jobject attrs, char *attribute, char *schema)
{
	if (!attrs)
		return NULL;

	if(!schema)
		schema = "http://schemas.android.com/apk/res/android";

	jstring string = (jstring)(*env)->CallObjectMethod(env, attrs, handle_cache.attribute_set.getAttributeValue_string, _JSTRING(schema), _JSTRING(attribute));
	return string ? _CSTRING(string) : NULL;
}

int attribute_set_get_int(JNIEnv *env, jobject attrs, char *attribute, char *schema, int default_value)
{
	if (!attrs)
		return default_value;

	if(!schema)
		schema = "http://schemas.android.com/apk/res/android";

	return (*env)->CallIntMethod(env, attrs, handle_cache.attribute_set.getAttributeValue_int, _JSTRING(schema), _JSTRING(attribute), default_value);
}

JavaVM *jvm;

// TODO: use this everywhere, not just for gdb helper functions
JNIEnv * get_jni_env(void)
{
	JNIEnv *env;
	(*jvm)->GetEnv(jvm, (void**)&env, JNI_VERSION_1_6);
	return env;
}

JNIEnv * _gdb_get_jni_env(void)
{
	return get_jni_env();
}

void _gdb_get_java_stack_trace(void)
{
	JNIEnv *env = get_jni_env();
	(*env)->ExceptionDescribe(env);
}

void _gdb_force_java_stack_trace(void)
{
	JNIEnv *env = get_jni_env();
	(*env)->ThrowNew(env, (*env)->FindClass(env, "java/lang/Exception"), "forced stack trace");
	(*env)->ExceptionDescribe(env);
	(*env)->ExceptionClear(env);
}

void set_up_handle_cache(JNIEnv *env)
{
	(*env)->GetJavaVM(env, &jvm);

	handle_cache.activity.class = _REF((*env)->FindClass(env, "android/app/Activity"));
	if((*env)->ExceptionCheck(env))
		(*env)->ExceptionDescribe(env);
	handle_cache.activity.onCreate = _METHOD(handle_cache.activity.class, "onCreate", "(Landroid/os/Bundle;)V");
	handle_cache.activity.onPostCreate = _METHOD(handle_cache.activity.class, "onPostCreate", "(Landroid/os/Bundle;)V");
	handle_cache.activity.onStart = _METHOD(handle_cache.activity.class, "onStart", "()V");
	handle_cache.activity.onWindowFocusChanged = _METHOD(handle_cache.activity.class, "onWindowFocusChanged", "(Z)V");
	handle_cache.activity.onResume = _METHOD(handle_cache.activity.class, "onResume", "()V");
	handle_cache.activity.onPostResume = _METHOD(handle_cache.activity.class, "onPostResume", "()V");
	handle_cache.activity.onDestroy = _METHOD(handle_cache.activity.class, "onDestroy", "()V");
	handle_cache.activity.onStop = _METHOD(handle_cache.activity.class, "onStop", "()V");
	handle_cache.activity.onPause = _METHOD(handle_cache.activity.class, "onPause", "()V");
	handle_cache.activity.onBackPressed = _METHOD(handle_cache.activity.class, "onBackPressed", "()V");

	handle_cache.attribute_set.class = _REF((*env)->FindClass(env, "android/util/AttributeSet"));
	if((*env)->ExceptionCheck(env))
		(*env)->ExceptionDescribe(env);
	handle_cache.attribute_set.getAttributeValue_string = _METHOD(handle_cache.attribute_set.class, "getAttributeValue", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
	handle_cache.attribute_set.getAttributeValue_int = _METHOD(handle_cache.attribute_set.class, "getAttributeIntValue", "(Ljava/lang/String;Ljava/lang/String;I)I");

	handle_cache.array_list.class = _REF((*env)->FindClass(env, "java/util/ArrayList"));
	handle_cache.array_list.add = _METHOD(handle_cache.array_list.class, "add", "(Ljava/lang/Object;)Z");
	handle_cache.array_list.remove = _METHOD(handle_cache.array_list.class, "remove", "(Ljava/lang/Object;)Z");
	handle_cache.array_list.get = _METHOD(handle_cache.array_list.class, "get", "(I)Ljava/lang/Object;");
	handle_cache.array_list.size = _METHOD(handle_cache.array_list.class, "size", "()I");
	handle_cache.array_list.clear = _METHOD(handle_cache.array_list.class, "clear", "()V");

	handle_cache.paint.class = _REF((*env)->FindClass(env, "android/graphics/Paint"));
	handle_cache.paint.getColor = _METHOD(handle_cache.paint.class, "getColor", "()I");

	handle_cache.motion_event.class = _REF((*env)->FindClass(env, "android/view/MotionEvent"));
	handle_cache.motion_event.constructor = _METHOD(handle_cache.motion_event.class, "<init>", "(IIJ[I[F)V");
	handle_cache.motion_event.constructor_single = _METHOD(handle_cache.motion_event.class, "<init>", "(IIJFFFF)V");

	handle_cache.sensor_event.class = _REF((*env)->FindClass(env, "android/hardware/SensorEvent"));
	handle_cache.sensor_event.constructor = _METHOD(handle_cache.sensor_event.class, "<init>", "([FLandroid/hardware/Sensor;)V");

	handle_cache.audio_track_periodic_listener.class = _REF((*env)->FindClass(env, "android/media/AudioTrack$OnPlaybackPositionUpdateListener"));
	handle_cache.audio_track_periodic_listener.onPeriodicNotification = _METHOD(handle_cache.audio_track_periodic_listener.class, "onPeriodicNotification", "(Landroid/media/AudioTrack;)V");

	handle_cache.input_queue_callback.class = _REF((*env)->FindClass(env, "android/view/InputQueue$Callback"));
	handle_cache.input_queue_callback.onInputQueueCreated = _METHOD(handle_cache.input_queue_callback.class, "onInputQueueCreated", "(Landroid/view/InputQueue;)V");

	handle_cache.surface_view.class = _REF((*env)->FindClass(env, "android/view/SurfaceView"));
	handle_cache.surface_view.surfaceCreated = _METHOD(handle_cache.surface_view.class, "surfaceCreated", "()V");
	handle_cache.surface_view.surfaceChanged = _METHOD(handle_cache.surface_view.class, "surfaceChanged", "(III)V");

	handle_cache.view.class = _REF((*env)->FindClass(env, "android/view/View"));
	if((*env)->ExceptionCheck(env))
		(*env)->ExceptionDescribe(env);
	handle_cache.view.setLayoutParams = _METHOD(handle_cache.view.class, "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V");
	if((*env)->ExceptionCheck(env))
		(*env)->ExceptionDescribe(env);
	handle_cache.view.onDraw = _METHOD(handle_cache.view.class, "onDraw", "(Landroid/graphics/Canvas;)V");
	handle_cache.view.dispatchDraw = _METHOD(handle_cache.view.class, "dispatchDraw", "(Landroid/graphics/Canvas;)V");
	handle_cache.view.draw = _METHOD(handle_cache.view.class, "draw", "(Landroid/graphics/Canvas;)V");
	handle_cache.view.onMeasure = _METHOD(handle_cache.view.class, "onMeasure", "(II)V");
	handle_cache.view.onLayout = _METHOD(handle_cache.view.class, "onLayout", "(ZIIII)V");
	handle_cache.view.getMeasuredWidth = _METHOD(handle_cache.view.class, "getMeasuredWidth", "()I");
	handle_cache.view.getMeasuredHeight = _METHOD(handle_cache.view.class, "getMeasuredHeight", "()I");
	handle_cache.view.getSuggestedMinimumWidth = _METHOD(handle_cache.view.class, "getSuggestedMinimumWidth", "()I");
	handle_cache.view.getSuggestedMinimumHeight = _METHOD(handle_cache.view.class, "getSuggestedMinimumHeight", "()I");
	handle_cache.view.setMeasuredDimension = _METHOD(handle_cache.view.class, "setMeasuredDimension", "(II)V");
	handle_cache.view.onGenericMotionEvent = _METHOD(handle_cache.view.class, "onGenericMotionEvent", "(Landroid/view/MotionEvent;)Z");
	handle_cache.view.computeScroll = _METHOD(handle_cache.view.class, "computeScroll", "()V");
	handle_cache.view.getScrollX = _METHOD(handle_cache.view.class, "getScrollX", "()I");
	handle_cache.view.getScrollY = _METHOD(handle_cache.view.class, "getScrollY", "()I");
	handle_cache.view.performClick = _METHOD(handle_cache.view.class, "performClick", "()Z");
	handle_cache.view.onTouchEvent = _METHOD(handle_cache.view.class, "onTouchEvent", "(Landroid/view/MotionEvent;)Z");
	handle_cache.view.onTouchEventInternal = _METHOD(handle_cache.view.class, "onTouchEventInternal", "(Landroid/view/MotionEvent;Z)Z");
	handle_cache.view.dispatchTouchEvent = _METHOD(handle_cache.view.class, "dispatchTouchEvent", "(Landroid/view/MotionEvent;)Z");
	handle_cache.view.onInterceptTouchEvent = _METHOD(handle_cache.view.class, "onInterceptTouchEvent", "(Landroid/view/MotionEvent;)Z");
	handle_cache.view.layoutInternal = _METHOD(handle_cache.view.class, "layoutInternal", "(II)V");
	handle_cache.view.measure = _METHOD(handle_cache.view.class, "measure", "(II)V");
	handle_cache.view.performLongClick = _METHOD(handle_cache.view.class, "performLongClick", "(FF)Z");
	handle_cache.view.getId = _METHOD(handle_cache.view.class, "getId", "()I");
	handle_cache.view.getIdName = _METHOD(handle_cache.view.class, "getIdName", "()Ljava/lang/String;");
	handle_cache.view.getAllSuperClasses = _METHOD(handle_cache.view.class, "getAllSuperClasses", "()Ljava/lang/String;");
	handle_cache.view.dispatchKeyEvent = _METHOD(handle_cache.view.class, "dispatchKeyEvent", "(Landroid/view/KeyEvent;)Z");
	handle_cache.view.onKeyDown = _METHOD(handle_cache.view.class, "onKeyDown", "(ILandroid/view/KeyEvent;)Z");

	handle_cache.view_group.class = _REF((*env)->FindClass(env, "android/view/ViewGroup"));
	handle_cache.view_group.dispatchTouchEvent = _METHOD(handle_cache.view_group.class, "dispatchTouchEvent", "(Landroid/view/MotionEvent;)Z");

	handle_cache.asset_manager.class = _REF((*env)->FindClass(env, "android/content/res/AssetManager"));
	handle_cache.asset_manager.extractFromAPK = _STATIC_METHOD(handle_cache.asset_manager.class, "extractFromAPK", "(Ljava/lang/String;Ljava/lang/String;)V");

	handle_cache.context.class = _REF((*env)->FindClass(env, "android/content/Context"));
	if((*env)->ExceptionCheck(env))
		(*env)->ExceptionDescribe(env);
	handle_cache.context.get_package_name = _METHOD(handle_cache.context.class, "getPackageName", "()Ljava/lang/String;");
	if((*env)->ExceptionCheck(env))
		(*env)->ExceptionDescribe(env);
	handle_cache.context.sendBroadcast = _METHOD(handle_cache.context.class, "sendBroadcast", "(Landroid/content/Intent;)V");

	handle_cache.application.class = _REF((*env)->FindClass(env, "android/app/Application"));
	handle_cache.application.get_app_icon_path = _METHOD(handle_cache.application.class, "get_app_icon_path", "()Ljava/lang/String;");

	handle_cache.looper.class = _REF((*env)->FindClass(env, "android/os/Looper"));
	handle_cache.looper.loop = _STATIC_METHOD(handle_cache.looper.class, "loop", "()V");
	handle_cache.looper.prepareMainLooper = _STATIC_METHOD(handle_cache.looper.class, "prepareMainLooper", "()V");

	handle_cache.key_event.class = _REF((*env)->FindClass(env, "android/view/KeyEvent"));
	handle_cache.key_event.constructor = _METHOD(handle_cache.key_event.class, "<init>", "(II)V");

	handle_cache.drawable.class = _REF((*env)->FindClass(env, "android/graphics/drawable/Drawable"));
	handle_cache.drawable.draw = _METHOD(handle_cache.drawable.class, "draw", "(Landroid/graphics/Canvas;)V");
	handle_cache.drawable.setBounds = _METHOD(handle_cache.drawable.class, "setBounds", "(IIII)V");

	handle_cache.intent.class = _REF((*env)->FindClass(env, "android/content/Intent"));
	handle_cache.intent.constructor = _METHOD(handle_cache.intent.class, "<init>", "()V");
	handle_cache.intent.putExtraCharSequence = _METHOD(handle_cache.intent.class, "putExtra", "(Ljava/lang/String;Ljava/lang/CharSequence;)Landroid/content/Intent;");
	handle_cache.intent.putExtraByteArray = _METHOD(handle_cache.intent.class, "putExtra", "(Ljava/lang/String;[B)Landroid/content/Intent;");

	handle_cache.instrumentation.class = _REF((*env)->FindClass(env, "android/app/Instrumentation"));

	handle_cache.webview.class = _REF((*env)->FindClass(env, "android/webkit/WebView"));
	handle_cache.webview.internalGetAssetManager = _METHOD(handle_cache.webview.class, "internalGetAssetManager", "()Landroid/content/res/AssetManager;");
	handle_cache.webview.internalLoadChanged = _METHOD(handle_cache.webview.class, "internalLoadChanged", "(ILjava/lang/String;)V");

	handle_cache.canvas.class = _REF((*env)->FindClass(env, "android/graphics/Canvas"));
	handle_cache.canvas.drawText = _METHOD(handle_cache.canvas.class, "drawText", "(Ljava/lang/CharSequence;IIFFLandroid/graphics/Paint;)V");
}

void extract_from_apk(const char *path, const char *target) {
	JNIEnv *env = get_jni_env();
	(*env)->CallStaticVoidMethod(env, handle_cache.asset_manager.class, handle_cache.asset_manager.extractFromAPK, _JSTRING(path), _JSTRING(target));
}

/* logging with fallback to stderr */

typedef int __android_log_vprint_type(int prio, const char *tag, const char *fmt, va_list ap);

static int fallback_verbose_log(int prio, const char *tag, const char *fmt, va_list ap)
{
	int ret;

	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);
	static char buf[1024];
	ret = vsnprintf(buf, sizeof(buf), fmt, ap);
	fprintf(stderr, "%w64u: %s\n", (uint64_t)pthread_self(), buf);
	pthread_mutex_unlock(&mutex);

	return ret;
}

static int android_log_vprintf(int prio, const char *tag, const char *fmt, va_list ap)
{

	static __android_log_vprint_type *_android_log_vprintf = NULL;
	if(!_android_log_vprintf) {
		_android_log_vprintf = dlsym(RTLD_DEFAULT, "__android_log_vprint");

		if(!_android_log_vprintf) {
			_android_log_vprintf = &fallback_verbose_log;
		}
	}

	return _android_log_vprintf(prio, tag, fmt, ap);
}

int android_log_printf(android_LogPriority prio, const char *tag, const char *fmt, ...)
{
	int ret;

	va_list ap;
	va_start(ap, fmt);

	ret = android_log_vprintf(prio, tag, fmt, ap);

	va_end(ap);

	return ret;
}

void *get_nio_buffer(JNIEnv *env, jobject buffer, jarray *array_ref, jbyte **array)
{
	jclass class;
	void *pointer;
	int elementSizeShift, position;

	if (!buffer) {
		*array_ref = NULL;
		return NULL;
	}
	class = _CLASS(buffer);
	pointer = _PTR((*env)->GetLongField(env, buffer, _FIELD_ID(class, "address", "J")));
	elementSizeShift = (*env)->GetIntField(env, buffer, _FIELD_ID(class, "_elementSizeShift", "I"));
	position = (*env)->GetIntField(env, buffer, _FIELD_ID(class, "position", "I"));
	if (pointer) {   // buffer is direct
		*array_ref = NULL;
		pointer += position << elementSizeShift;
	} else {   // buffer is indirect
		*array_ref = (*env)->CallObjectMethod(env, buffer, _METHOD(class, "array", "()Ljava/lang/Object;"));
		jint offset = (*env)->CallIntMethod(env, buffer, _METHOD(class, "arrayOffset", "()I"));
		pointer = *array = (*env)->GetPrimitiveArrayCritical(env, *array_ref, NULL);
		pointer += (offset + position) << elementSizeShift;
	}
	return pointer;
}

void release_nio_buffer(JNIEnv *env, jarray array_ref, jbyte *array)
{
	if (array_ref)
		(*env)->ReleasePrimitiveArrayCritical(env, array_ref, array, 0);
}

int get_nio_buffer_size(JNIEnv *env, jobject buffer)
{
	jclass class = _CLASS(buffer);;
	int limit = (*env)->GetIntField(env, buffer, _FIELD_ID(class, "limit", "I"));
	int position = (*env)->GetIntField(env, buffer, _FIELD_ID(class, "position", "I"));

	return limit - position;
}


/* Calling these functions while snapshotting will cause Gtk to not snapshot the affected widgets.
 * Below are "safe" wrappers which will postpone the calls if inside a snapshot.
 * Specifically, gtk_widget_add_tick_callback will make sure the calls are made in the next
 * Update phase. */

/* callbacks */
static gboolean queue_set_text(GtkWidget *label, GdkFrameClock *frame_clock, gpointer str)
{
	gtk_label_set_text(GTK_LABEL(label), str);
	/* we always call strdup so we always want to free */
	free(str);
	return G_SOURCE_REMOVE;
}

static gboolean queue_queue_allocate(GtkWidget *widget, GdkFrameClock *frame_clock, gpointer user_data)
{
	gtk_widget_queue_allocate(widget);
	return G_SOURCE_REMOVE;
}

static gboolean queue_queue_resize(GtkWidget *widget, GdkFrameClock *frame_clock, gpointer user_data)
{
	gtk_widget_queue_resize(widget);
	return G_SOURCE_REMOVE;
}

/* Some functions call gtk_widget_queue_allocate or similar internally.
 * To prevent that from breaking the snapshotting process, when called at the wrong time,
 * we have to follow those functions with this pile of hacks that will unset the problematic flags. */
extern int snapshot_in_progress;
void atl_ensure_widget_snapshotability(GtkWidget *widget)
{
	if(snapshot_in_progress) {
		GtkAllocation allocation;
		G_GNUC_BEGIN_IGNORE_DEPRECATIONS
		/* we probably don't need to use this deprecated function but it sure is convenient */
		gtk_widget_get_allocation(widget, &allocation);
		G_GNUC_END_IGNORE_DEPRECATIONS
		/* this clears resize request, which seems to be necessary in some cases */
		gtk_widget_get_request_mode(widget);
		gtk_widget_size_allocate(widget, &allocation, gtk_widget_get_baseline(widget));
		gtk_widget_add_tick_callback(widget, queue_queue_allocate, NULL, NULL);

		/* the problematic flags get set all the way up the hierarchy */
		GtkWidget *parent = gtk_widget_get_parent(widget);
		if (parent) {
			atl_ensure_widget_snapshotability(parent);
		}
	}
}

void atl_safe_gtk_label_set_text(GtkLabel* label, const char* str)
{
	if(!snapshot_in_progress) {
		gtk_label_set_text(label, str);
	} else {
		/* strdup since the string may not exist by the time the callback runs */
		gtk_widget_add_tick_callback(GTK_WIDGET(label), queue_set_text, (gpointer)strdup(str), NULL);
	}
}

void atl_safe_gtk_widget_set_visible(GtkWidget *widget, gboolean visible)
{
	gtk_widget_set_visible(widget, visible);
	GtkWidget *parent = gtk_widget_get_parent(widget);
	if (parent) {
		atl_ensure_widget_snapshotability(parent);
	}
}

void atl_safe_gtk_widget_queue_allocate(GtkWidget *widget)
{
	if(!snapshot_in_progress) {
		gtk_widget_queue_allocate(widget);
	} else {
		gtk_widget_add_tick_callback(widget, queue_queue_allocate, NULL, NULL);
	}
}

void atl_safe_gtk_widget_queue_resize(GtkWidget *widget)
{
	if(!snapshot_in_progress) {
		gtk_widget_queue_resize(widget);
	} else {
		gtk_widget_add_tick_callback(widget, queue_queue_resize, NULL, NULL);
	}
}
