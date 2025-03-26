#ifndef _UTILS_H_
#define _UTILS_H_

#include <jni.h>

#include "defines.h"

struct handle_cache {
	struct {
		jclass class;
		jmethodID onCreate;
		jmethodID onPostCreate;
		jmethodID onStart;
		jmethodID onResume;
		jmethodID onPostResume;
		jmethodID onWindowFocusChanged;
		jmethodID onDestroy;
		jmethodID onStop;
		jmethodID onPause;
		jmethodID onBackPressed;
	} activity;
	struct {
		jclass class;
		jmethodID getAttributeValue_string;
		jmethodID getAttributeValue_int;
	} attribute_set;
	struct {
		jclass class;
		jmethodID add;
		jmethodID remove;
		jmethodID get;
		jmethodID size;
		jmethodID clear;
	} array_list;
	struct {
		jclass class;
		jmethodID getColor;
	} paint;
	struct {
		jclass class;
		jmethodID constructor;
		jmethodID constructor_single;
	} motion_event;
	struct {
		jclass class;
		jmethodID constructor;
	} sensor_event;
	struct {
		jclass class;
		jmethodID onPeriodicNotification;
	} audio_track_periodic_listener;
	struct {
		jclass class;
		jmethodID onInputQueueCreated;
	} input_queue_callback;
	struct {
		jclass class;
		jmethodID surfaceCreated;
		jmethodID surfaceChanged;
	} surface_view;
	struct {
		jclass class;
		jmethodID setLayoutParams;
		jmethodID onDraw;
		jmethodID dispatchDraw;
		jmethodID draw;
		jmethodID onMeasure;
		jmethodID onLayout;
		jmethodID getMeasuredWidth;
		jmethodID getMeasuredHeight;
		jmethodID getSuggestedMinimumWidth;
		jmethodID getSuggestedMinimumHeight;
		jmethodID setMeasuredDimension;
		jmethodID onGenericMotionEvent;
		jmethodID computeScroll;
		jmethodID getScrollX;
		jmethodID getScrollY;
		jmethodID performClick;
		jmethodID onTouchEvent;
		jmethodID onTouchEventInternal;
		jmethodID dispatchTouchEvent;
		jmethodID onInterceptTouchEvent;
		jmethodID layoutInternal;
		jmethodID measure;
		jmethodID performLongClick;
		jmethodID getId;
		jmethodID getIdName;
		jmethodID getAllSuperClasses;
		jmethodID dispatchKeyEvent;
		jmethodID onKeyDown;
	} view;
	struct {
		jclass class;
		jmethodID dispatchTouchEvent;
	} view_group;
	struct {
		jclass class;
		jmethodID extractFromAPK;
	} asset_manager;
	struct {
		jclass class;
		jmethodID get_package_name;
	} context;
	struct {
		jclass class;
		jmethodID get_app_icon_path;
	} application;
	struct {
		jclass class;
		jmethodID loop;
		jmethodID prepareMainLooper;
	} looper;
	struct {
		jclass class;
		jmethodID constructor;
	} key_event;
	struct {
		jclass class;
		jmethodID draw;
		jmethodID setBounds;
	} drawable;
	struct {
		jclass class;
		jmethodID constructor;
		jmethodID putExtraCharSequence;
	} intent;
	struct {
		jclass class;
		jmethodID internalGetAssetManager;
		jmethodID internalLoadChanged;
	} webview;
	struct {
		jclass class;
		jmethodID onCreate;
		jmethodID start;
	} instrumentation;
	struct {
		jclass class;
		jmethodID drawText;
	} canvas;
};

extern struct handle_cache handle_cache;

JNIEnv * get_jni_env(void);

const char * attribute_set_get_string(JNIEnv *env, jobject attrs, char *attribute, char *schema);
int attribute_set_get_int(JNIEnv *env, jobject attrs, char *attribute, char *schema, int default_value);
void set_up_handle_cache(JNIEnv *env);
void extract_from_apk(const char *path, const char *target);
char *get_app_data_dir();

void prepare_main_looper(JNIEnv* env);

/* we don't (currently?) install the headers for liblog */
typedef enum {
	LOG_ID_MAIN = 0,
	LOG_ID_RADIO = 1,
	LOG_ID_EVENTS = 2,
	LOG_ID_SYSTEM = 3,

	LOG_ID_MAX
} log_id_t;

typedef enum android_LogPriority {
    ANDROID_LOG_UNKNOWN = 0,
    ANDROID_LOG_DEFAULT,    /* only for SetMinPriority() */
    ANDROID_LOG_VERBOSE,
    ANDROID_LOG_DEBUG,
    ANDROID_LOG_INFO,
    ANDROID_LOG_WARN,
    ANDROID_LOG_ERROR,
    ANDROID_LOG_FATAL,
    ANDROID_LOG_SILENT,     /* only for SetMinPriority(); must be last */
} android_LogPriority;

/* TODO: do we really need the bufID, or can we use our function below which has a stderr fallback */
int __android_log_buf_write(int bufID, int prio, const char *tag, const char *text);

/* defined in util.c */
int android_log_printf(android_LogPriority prio, const char *tag, const char *fmt, ...);

void *get_nio_buffer(JNIEnv *env, jobject buffer, jarray *array_ref, jbyte **array);
void release_nio_buffer(JNIEnv *env, jarray array_ref, jbyte *array);
int get_nio_buffer_size(JNIEnv *env, jobject buffer);

#endif
