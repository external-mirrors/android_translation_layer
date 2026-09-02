#ifndef _UPCALLS_H_
#define _UPCALLS_H_

#include <jni.h>
#include "../defines.h"

struct handle_cache {
	struct {
		jclass class;
		jmethodID setSelectedFile;
	} ATLMediaContentProvider;

	struct {
		jclass class;
		jmethodID createMainActivity;
		jmethodID fileChooserResultCallback;
		jmethodID onBackPressed;
		jmethodID onCreate;
		jmethodID onDestroy;
		jmethodID onNewIntent;
		jmethodID onPause;
		jmethodID onPostCreate;
		jmethodID onPostResume;
		jmethodID onResume;
		jmethodID onStart;
		jmethodID onStop;
		jmethodID onWindowFocusChanged;
	} Activity;

	struct {
		jclass class;
		jmethodID getCount;
	} Adapter;

	struct {
		jclass class;
		jmethodID onItemSelected;
	} AdapterView__OnItemSelectedListener;

	struct {
		jclass class;
		jmethodID get_app_icon_paintable;
		jmethodID get_app_icon_path;
		jmethodID get_app_label;
		jmethodID get_supported_mime_types;
		jmethodID onCreate;
	} Application;

	struct {
		jclass class;
		jmethodID add;
		jmethodID clear;
		jmethodID get;
		jmethodID remove;
		jmethodID size;
	} ArrayList;

	struct {
		jclass class;
		jmethodID extractFromAPK;
	} AssetManager;

	struct {
		jclass class;
		jmethodID getAttributeIntValue;
		jmethodID getAttributeValue;
	} AttributeSet;

	struct {
		jclass class;
		jmethodID onPeriodicNotification;
	} AudioTrack__OnPlaybackPositionUpdateListener;

	struct {
		jclass class;
		jmethodID get;
		jmethodID keySet;
	} BaseBundle;

	struct {
		jclass class;
		jmethodID getTexture;
		jmethodID recycle;
	} Bitmap;

	struct {
		jclass class;
		jmethodID array;
		jmethodID arrayOffset;
	} Buffer;

	struct {
		jclass class;
		jmethodID drawText;
	} Canvas;

	struct {
		jclass class;
		jmethodID toString;
	} CharSequence;

	struct {
		jclass class;
		jmethodID getClassLoader;
		jmethodID getName;
	} Class;

	struct {
		jclass class;
		jmethodID onCheckedChanged;
	} CompoundButton__OnCheckedChangeListener;

	struct {
		jclass class;
		jmethodID onAvailable;
		jmethodID onLost;
	} ConnectivityManager__NetworkCallback;

	struct {
		jclass class;
		jmethodID createContentProviders;
	} ContentProvider;

	struct {
		jclass class;
		jmethodID createApplication;
		jmethodID getPackageName;
		jmethodID resolveActivityInternal;
		jmethodID sendBroadcast;
		jmethodID startActivity;
		jmethodID startService;
	} Context;

	struct {
		jclass class;
		jmethodID onDateChange;
	} DatePicker;

	struct {
		jclass class;
		jmethodID dismiss;
	} Dialog;

	struct {
		jclass class;
		jmethodID dismiss;
	} DialogInterface;

	struct {
		jclass class;
		jmethodID onClick;
	} DialogInterface__OnClickListener;

	struct {
		jclass class;
		jmethodID draw;
		jmethodID getIntrinsicHeight;
		jmethodID getIntrinsicWidth;
		jmethodID setBounds;
	} Drawable;

	struct {
		jclass class;
		jmethodID constructor;
	} GVariantBuilderParcel;

	struct {
		jclass class;
		jmethodID constructor;
	} GVariantIterParcel;

	struct {
		jclass class;
		jmethodID constructor;
	} GskCanvas;

	struct {
		jclass class;
		jmethodID commitText;
		jmethodID deleteSurroundingText;
		jmethodID getTextAfterCursor;
		jmethodID getTextBeforeCursor;
	} InputConnection;

	struct {
		jclass class;
		jmethodID onInputQueueCreated;
	} InputQueue__Callback;

	struct {
		jclass class;
		jmethodID read;
	} InputStream;

	struct {
		jclass class;
		jmethodID create;
	} Instrumentation;

	struct {
		jclass class;
		jmethodID constructor;
		jmethodID getDataString;
		jmethodID putExtraByteArray;
		jmethodID putExtraCharSequence;
		jmethodID putExtraInt;
		jmethodID putExtraLong;
		jmethodID putExtraParcelable;
		jmethodID setClassName;
	} Intent;

	struct {
		jclass class;
		jmethodID constructor;
	} KeyEvent;

	struct {
		jclass class;
		jmethodID locationUpdated;
	} LocationManager;

	struct {
		jclass class;
		jmethodID loop;
		jmethodID prepareMainLooper;
	} Looper;

	struct {
		jclass class;
		jmethodID onCompletion;
	} MediaPlayer__OnCompletionListener;

	struct {
		jclass class;
		jmethodID onPause;
		jmethodID onPlay;
		jmethodID onSeekTo;
	} MediaSession__Callback;

	struct {
		jclass class;
		jmethodID constructor;
		jmethodID constructor_scroll;
		jmethodID constructor_single;
	} MotionEvent;

	struct {
		jclass class;
		jmethodID getColor;
	} Paint;

	struct {
		jclass class;
		jmethodID readParcelable;
		jmethodID writeParcelable;
	} Parcel;

	struct {
		jclass class;
		jmethodID menuItemClickCallback;
	} PopupMenu;

	struct {
		jclass class;
		jmethodID onDismiss;
	} PopupWindow__OnDismissListener;

	struct {
		jclass class;
		jmethodID getRuntime;
		jmethodID loadLibrary;
	} Runtime;

	struct {
		jclass class;
		jmethodID dispatchCallback;
	} SQLiteCustomFunction;

	struct {
		jclass class;
		jmethodID onProgressChanged;
		jmethodID onStartTrackingTouch;
		jmethodID onStopTrackingTouch;
	} SeekBar__OnSeekBarChangeListener;

	struct {
		jclass class;
		jmethodID constructor;
	} SensorEvent;

	struct {
		jclass class;
		jmethodID onSensorChanged;
	} SensorEventListener;

	struct {
		jclass class;
		jmethodID toArray;
	} Set;

	struct {
		jclass class;
		jmethodID constructor;
	} SpannableStringBuilder;

	struct {
		jclass class;
		jmethodID getDropDownView;
	} SpinnerAdapter;

	struct {
		jclass class;
		jmethodID surfaceChanged;
		jmethodID surfaceCreated;
	} SurfaceView;

	struct {
		jclass class;
		jmethodID exit;
	} System;

	struct {
		jclass class;
		jmethodID onEditorAction;
	} TextView__OnEditorActionListener;

	struct {
		jclass class;
		jmethodID afterTextChanged;
		jmethodID onTextChanged;
	} TextWatcher;

	struct {
		jclass class;
		jmethodID onTimeChange;
	} TimePicker;

	struct {
		jclass class;
		jmethodID parse;
	} Uri;

	struct {
		jclass class;
		jmethodID computeScroll;
		jmethodID dispatchDraw;
		jmethodID dispatchGenericMotionEvent;
		jmethodID dispatchHoverEvent;
		jmethodID dispatchKeyEvent;
		jmethodID dispatchTouchEvent;
		jmethodID draw;
		jmethodID getAllSuperClasses;
		jmethodID getId;
		jmethodID getIdName;
		jmethodID getMeasuredHeight;
		jmethodID getMeasuredWidth;
		jmethodID getScrollX;
		jmethodID getScrollY;
		jmethodID getSuggestedMinimumHeight;
		jmethodID getSuggestedMinimumWidth;
		jmethodID layoutInternal;
		jmethodID measure;
		jmethodID onAttachedToWindow;
		jmethodID onDetachedFromWindow;
		jmethodID onDraw;
		jmethodID onGenericMotionEvent;
		jmethodID onInterceptTouchEvent;
		jmethodID onKeyDown;
		jmethodID onLayout;
		jmethodID onMeasure;
		jmethodID onTouchEvent;
		jmethodID onTouchEventInternal;
		jmethodID performClick;
		jmethodID performLongClick;
		jmethodID setLayoutParams;
		jmethodID setMeasuredDimension;
	} View;

	struct {
		jclass class;
		jmethodID dispatchTouchEvent;
	} ViewGroup;

	struct {
		jclass class;
		jmethodID dispatchOnGlobalLayout;
	} ViewTreeObserver;

	struct {
		jclass class;
		jmethodID internalGetAssetManager;
		jmethodID internalLoadChanged;
	} WebView;
};
extern struct handle_cache handle_cache;

__attribute__((always_inline)) inline jclass J_get_class__Activity(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Activity.class))
		handle_cache.Activity.class = _REF((*env)->FindClass(env, "android/app/Activity"));

	return handle_cache.Activity.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__createMainActivity(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.createMainActivity == 0))
		handle_cache.Activity.createMainActivity = (*env)->GetStaticMethodID(env, J_get_class__Activity(env), "createMainActivity", "(Ljava/lang/String;JLjava/lang/String;)Landroid/app/Activity;");

	return handle_cache.Activity.createMainActivity;
}

__attribute__((always_inline)) inline jobject J__Activity__createMainActivity(JNIEnv *env, jstring className, jlong native_window, jstring uriString)
{
	jclass class = J_get_class__Activity(env);
	return (*env)->CallStaticObjectMethod(env, class, J_get_method__Activity__createMainActivity(env), className, native_window, uriString);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__fileChooserResultCallback(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.fileChooserResultCallback == 0))
		handle_cache.Activity.fileChooserResultCallback = (*env)->GetMethodID(env, J_get_class__Activity(env), "fileChooserResultCallback", "(IIILjava/lang/String;)V");

	return handle_cache.Activity.fileChooserResultCallback;
}

__attribute__((always_inline)) inline void J__Activity__fileChooserResultCallback(JNIEnv *env, jobject this, jint requestCode, jint resultCode, jint action, jstring uri)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__fileChooserResultCallback(env), requestCode, resultCode, action, uri);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onBackPressed(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onBackPressed == 0))
		handle_cache.Activity.onBackPressed = (*env)->GetMethodID(env, J_get_class__Activity(env), "onBackPressed", "()V");

	return handle_cache.Activity.onBackPressed;
}

__attribute__((always_inline)) inline void J__Activity__onBackPressed(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onBackPressed(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onCreate(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onCreate == 0))
		handle_cache.Activity.onCreate = (*env)->GetMethodID(env, J_get_class__Activity(env), "onCreate", "(Landroid/os/Bundle;)V");

	return handle_cache.Activity.onCreate;
}

__attribute__((always_inline)) inline void J__Activity__onCreate(JNIEnv *env, jobject this, jobject savedInstanceState)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onCreate(env), savedInstanceState);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onDestroy(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onDestroy == 0))
		handle_cache.Activity.onDestroy = (*env)->GetMethodID(env, J_get_class__Activity(env), "onDestroy", "()V");

	return handle_cache.Activity.onDestroy;
}

__attribute__((always_inline)) inline void J__Activity__onDestroy(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onDestroy(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onNewIntent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onNewIntent == 0))
		handle_cache.Activity.onNewIntent = (*env)->GetMethodID(env, J_get_class__Activity(env), "onNewIntent", "(Landroid/content/Intent;)V");

	return handle_cache.Activity.onNewIntent;
}

__attribute__((always_inline)) inline void J__Activity__onNewIntent(JNIEnv *env, jobject this, jobject intent)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onNewIntent(env), intent);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onPause(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onPause == 0))
		handle_cache.Activity.onPause = (*env)->GetMethodID(env, J_get_class__Activity(env), "onPause", "()V");

	return handle_cache.Activity.onPause;
}

__attribute__((always_inline)) inline void J__Activity__onPause(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onPause(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onPostCreate(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onPostCreate == 0))
		handle_cache.Activity.onPostCreate = (*env)->GetMethodID(env, J_get_class__Activity(env), "onPostCreate", "(Landroid/os/Bundle;)V");

	return handle_cache.Activity.onPostCreate;
}

__attribute__((always_inline)) inline void J__Activity__onPostCreate(JNIEnv *env, jobject this, jobject savedInstanceState)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onPostCreate(env), savedInstanceState);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onPostResume(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onPostResume == 0))
		handle_cache.Activity.onPostResume = (*env)->GetMethodID(env, J_get_class__Activity(env), "onPostResume", "()V");

	return handle_cache.Activity.onPostResume;
}

__attribute__((always_inline)) inline void J__Activity__onPostResume(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onPostResume(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onResume(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onResume == 0))
		handle_cache.Activity.onResume = (*env)->GetMethodID(env, J_get_class__Activity(env), "onResume", "()V");

	return handle_cache.Activity.onResume;
}

__attribute__((always_inline)) inline void J__Activity__onResume(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onResume(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onStart(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onStart == 0))
		handle_cache.Activity.onStart = (*env)->GetMethodID(env, J_get_class__Activity(env), "onStart", "()V");

	return handle_cache.Activity.onStart;
}

__attribute__((always_inline)) inline void J__Activity__onStart(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onStart(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onStop(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onStop == 0))
		handle_cache.Activity.onStop = (*env)->GetMethodID(env, J_get_class__Activity(env), "onStop", "()V");

	return handle_cache.Activity.onStop;
}

__attribute__((always_inline)) inline void J__Activity__onStop(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onStop(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Activity__onWindowFocusChanged(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Activity.onWindowFocusChanged == 0))
		handle_cache.Activity.onWindowFocusChanged = (*env)->GetMethodID(env, J_get_class__Activity(env), "onWindowFocusChanged", "(Z)V");

	return handle_cache.Activity.onWindowFocusChanged;
}

__attribute__((always_inline)) inline void J__Activity__onWindowFocusChanged(JNIEnv *env, jobject this, jboolean hasFocus)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Activity__onWindowFocusChanged(env), hasFocus);
}

__attribute__((always_inline)) inline jclass J_get_class__Application(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Application.class))
		handle_cache.Application.class = _REF((*env)->FindClass(env, "android/app/Application"));

	return handle_cache.Application.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Application__get_app_icon_paintable(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Application.get_app_icon_paintable == 0))
		handle_cache.Application.get_app_icon_paintable = (*env)->GetMethodID(env, J_get_class__Application(env), "get_app_icon_paintable", "()J");

	return handle_cache.Application.get_app_icon_paintable;
}

__attribute__((always_inline)) inline jlong J__Application__get_app_icon_paintable(JNIEnv *env, jobject this)
{
	return (*env)->CallLongMethod(env, this, J_get_method__Application__get_app_icon_paintable(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Application__get_app_icon_path(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Application.get_app_icon_path == 0))
		handle_cache.Application.get_app_icon_path = (*env)->GetMethodID(env, J_get_class__Application(env), "get_app_icon_path", "()Ljava/lang/String;");

	return handle_cache.Application.get_app_icon_path;
}

__attribute__((always_inline)) inline jstring J__Application__get_app_icon_path(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Application__get_app_icon_path(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Application__get_app_label(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Application.get_app_label == 0))
		handle_cache.Application.get_app_label = (*env)->GetMethodID(env, J_get_class__Application(env), "get_app_label", "()Ljava/lang/String;");

	return handle_cache.Application.get_app_label;
}

__attribute__((always_inline)) inline jstring J__Application__get_app_label(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Application__get_app_label(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Application__get_supported_mime_types(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Application.get_supported_mime_types == 0))
		handle_cache.Application.get_supported_mime_types = (*env)->GetMethodID(env, J_get_class__Application(env), "get_supported_mime_types", "()Ljava/lang/String;");

	return handle_cache.Application.get_supported_mime_types;
}

__attribute__((always_inline)) inline jstring J__Application__get_supported_mime_types(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Application__get_supported_mime_types(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Application__onCreate(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Application.onCreate == 0))
		handle_cache.Application.onCreate = (*env)->GetMethodID(env, J_get_class__Application(env), "onCreate", "()V");

	return handle_cache.Application.onCreate;
}

__attribute__((always_inline)) inline void J__Application__onCreate(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Application__onCreate(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Dialog(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Dialog.class))
		handle_cache.Dialog.class = _REF((*env)->FindClass(env, "android/app/Dialog"));

	return handle_cache.Dialog.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Dialog__dismiss(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Dialog.dismiss == 0))
		handle_cache.Dialog.dismiss = (*env)->GetMethodID(env, J_get_class__Dialog(env), "dismiss", "()V");

	return handle_cache.Dialog.dismiss;
}

__attribute__((always_inline)) inline void J__Dialog__dismiss(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Dialog__dismiss(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Instrumentation(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Instrumentation.class))
		handle_cache.Instrumentation.class = _REF((*env)->FindClass(env, "android/app/Instrumentation"));

	return handle_cache.Instrumentation.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Instrumentation__create(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Instrumentation.create == 0))
		handle_cache.Instrumentation.create = (*env)->GetStaticMethodID(env, J_get_class__Instrumentation(env), "create", "(Ljava/lang/String;Landroid/content/Intent;)Landroid/app/Instrumentation;");

	return handle_cache.Instrumentation.create;
}

__attribute__((always_inline)) inline jobject J__Instrumentation__create(JNIEnv *env, jstring className, jobject arguments)
{
	jclass class = J_get_class__Instrumentation(env);
	return (*env)->CallStaticObjectMethod(env, class, J_get_method__Instrumentation__create(env), className, arguments);
}

__attribute__((always_inline)) inline jclass J_get_class__ATLMediaContentProvider(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.ATLMediaContentProvider.class))
		handle_cache.ATLMediaContentProvider.class = _REF((*env)->FindClass(env, "android/atl/ATLMediaContentProvider"));

	return handle_cache.ATLMediaContentProvider.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__ATLMediaContentProvider__setSelectedFile(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ATLMediaContentProvider.setSelectedFile == 0))
		handle_cache.ATLMediaContentProvider.setSelectedFile = (*env)->GetMethodID(env, J_get_class__ATLMediaContentProvider(env), "setSelectedFile", "(Ljava/lang/String;)V");

	return handle_cache.ATLMediaContentProvider.setSelectedFile;
}

__attribute__((always_inline)) inline void J__ATLMediaContentProvider__setSelectedFile(JNIEnv *env, jobject this, jstring selectedFile)
{
	(*env)->CallVoidMethod(env, this, J_get_method__ATLMediaContentProvider__setSelectedFile(env), selectedFile);
}

__attribute__((always_inline)) inline jclass J_get_class__GVariantBuilderParcel(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.GVariantBuilderParcel.class))
		handle_cache.GVariantBuilderParcel.class = _REF((*env)->FindClass(env, "android/atl/GVariantBuilderParcel"));

	return handle_cache.GVariantBuilderParcel.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__GVariantBuilderParcel__constructor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.GVariantBuilderParcel.constructor == 0))
		handle_cache.GVariantBuilderParcel.constructor = (*env)->GetMethodID(env, J_get_class__GVariantBuilderParcel(env), "<init>", "(J)V");

	return handle_cache.GVariantBuilderParcel.constructor;
}

__attribute__((always_inline)) inline jobject J_new__GVariantBuilderParcel(JNIEnv *env, jlong builder)
{
	jclass class = J_get_class__GVariantBuilderParcel(env);
	return (*env)->NewObject(env, class, J_get_method__GVariantBuilderParcel__constructor(env), builder);
}

__attribute__((always_inline)) inline jclass J_get_class__GVariantIterParcel(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.GVariantIterParcel.class))
		handle_cache.GVariantIterParcel.class = _REF((*env)->FindClass(env, "android/atl/GVariantIterParcel"));

	return handle_cache.GVariantIterParcel.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__GVariantIterParcel__constructor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.GVariantIterParcel.constructor == 0))
		handle_cache.GVariantIterParcel.constructor = (*env)->GetMethodID(env, J_get_class__GVariantIterParcel(env), "<init>", "(J)V");

	return handle_cache.GVariantIterParcel.constructor;
}

__attribute__((always_inline)) inline jobject J_new__GVariantIterParcel(JNIEnv *env, jlong iter)
{
	jclass class = J_get_class__GVariantIterParcel(env);
	return (*env)->NewObject(env, class, J_get_method__GVariantIterParcel__constructor(env), iter);
}

__attribute__((always_inline)) inline jclass J_get_class__GskCanvas(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.GskCanvas.class))
		handle_cache.GskCanvas.class = _REF((*env)->FindClass(env, "android/atl/GskCanvas"));

	return handle_cache.GskCanvas.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__GskCanvas__constructor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.GskCanvas.constructor == 0))
		handle_cache.GskCanvas.constructor = (*env)->GetMethodID(env, J_get_class__GskCanvas(env), "<init>", "(J)V");

	return handle_cache.GskCanvas.constructor;
}

__attribute__((always_inline)) inline jobject J_new__GskCanvas(JNIEnv *env, jlong snapshot)
{
	jclass class = J_get_class__GskCanvas(env);
	return (*env)->NewObject(env, class, J_get_method__GskCanvas__constructor(env), snapshot);
}

__attribute__((always_inline)) inline jclass J_get_class__ContentProvider(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.ContentProvider.class))
		handle_cache.ContentProvider.class = _REF((*env)->FindClass(env, "android/content/ContentProvider"));

	return handle_cache.ContentProvider.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__ContentProvider__createContentProviders(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ContentProvider.createContentProviders == 0))
		handle_cache.ContentProvider.createContentProviders = (*env)->GetStaticMethodID(env, J_get_class__ContentProvider(env), "createContentProviders", "()V");

	return handle_cache.ContentProvider.createContentProviders;
}

__attribute__((always_inline)) inline void J__ContentProvider__createContentProviders(JNIEnv *env)
{
	jclass class = J_get_class__ContentProvider(env);
	return (*env)->CallStaticVoidMethod(env, class, J_get_method__ContentProvider__createContentProviders(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Context(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Context.class))
		handle_cache.Context.class = _REF((*env)->FindClass(env, "android/content/Context"));

	return handle_cache.Context.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Context__createApplication(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Context.createApplication == 0))
		handle_cache.Context.createApplication = (*env)->GetStaticMethodID(env, J_get_class__Context(env), "createApplication", "(J)Landroid/app/Application;");

	return handle_cache.Context.createApplication;
}

__attribute__((always_inline)) inline jobject J__Context__createApplication(JNIEnv *env, jlong native_window)
{
	jclass class = J_get_class__Context(env);
	return (*env)->CallStaticObjectMethod(env, class, J_get_method__Context__createApplication(env), native_window);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Context__getPackageName(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Context.getPackageName == 0))
		handle_cache.Context.getPackageName = (*env)->GetMethodID(env, J_get_class__Context(env), "getPackageName", "()Ljava/lang/String;");

	return handle_cache.Context.getPackageName;
}

__attribute__((always_inline)) inline jstring J__Context__getPackageName(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Context__getPackageName(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Context__resolveActivityInternal(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Context.resolveActivityInternal == 0))
		handle_cache.Context.resolveActivityInternal = (*env)->GetStaticMethodID(env, J_get_class__Context(env), "resolveActivityInternal", "(Landroid/content/Intent;)Landroid/app/Activity;");

	return handle_cache.Context.resolveActivityInternal;
}

__attribute__((always_inline)) inline jobject J__Context__resolveActivityInternal(JNIEnv *env, jobject intent)
{
	jclass class = J_get_class__Context(env);
	return (*env)->CallStaticObjectMethod(env, class, J_get_method__Context__resolveActivityInternal(env), intent);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Context__sendBroadcast(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Context.sendBroadcast == 0))
		handle_cache.Context.sendBroadcast = (*env)->GetMethodID(env, J_get_class__Context(env), "sendBroadcast", "(Landroid/content/Intent;)V");

	return handle_cache.Context.sendBroadcast;
}

__attribute__((always_inline)) inline void J__Context__sendBroadcast(JNIEnv *env, jobject this, jobject intent)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Context__sendBroadcast(env), intent);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Context__startActivity(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Context.startActivity == 0))
		handle_cache.Context.startActivity = (*env)->GetMethodID(env, J_get_class__Context(env), "startActivity", "(Landroid/content/Intent;)V");

	return handle_cache.Context.startActivity;
}

__attribute__((always_inline)) inline void J__Context__startActivity(JNIEnv *env, jobject this, jobject intent)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Context__startActivity(env), intent);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Context__startService(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Context.startService == 0))
		handle_cache.Context.startService = (*env)->GetMethodID(env, J_get_class__Context(env), "startService", "(Landroid/content/Intent;)Landroid/content/ComponentName;");

	return handle_cache.Context.startService;
}

__attribute__((always_inline)) inline jobject J__Context__startService(JNIEnv *env, jobject this, jobject intent)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Context__startService(env), intent);
}

__attribute__((always_inline)) inline jclass J_get_class__DialogInterface(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.DialogInterface.class))
		handle_cache.DialogInterface.class = _REF((*env)->FindClass(env, "android/content/DialogInterface"));

	return handle_cache.DialogInterface.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__DialogInterface__dismiss(JNIEnv *env)
{
	if (__unlikely__(handle_cache.DialogInterface.dismiss == 0))
		handle_cache.DialogInterface.dismiss = (*env)->GetMethodID(env, J_get_class__DialogInterface(env), "dismiss", "()V");

	return handle_cache.DialogInterface.dismiss;
}

__attribute__((always_inline)) inline void J__DialogInterface__dismiss(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__DialogInterface__dismiss(env));
}

__attribute__((always_inline)) inline jclass J_get_class__DialogInterface__OnClickListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.DialogInterface__OnClickListener.class))
		handle_cache.DialogInterface__OnClickListener.class = _REF((*env)->FindClass(env, "android/content/DialogInterface$OnClickListener"));

	return handle_cache.DialogInterface__OnClickListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__DialogInterface__OnClickListener__onClick(JNIEnv *env)
{
	if (__unlikely__(handle_cache.DialogInterface__OnClickListener.onClick == 0))
		handle_cache.DialogInterface__OnClickListener.onClick = (*env)->GetMethodID(env, J_get_class__DialogInterface__OnClickListener(env), "onClick", "(Landroid/content/DialogInterface;I)V");

	return handle_cache.DialogInterface__OnClickListener.onClick;
}

__attribute__((always_inline)) inline void J__DialogInterface__OnClickListener__onClick(JNIEnv *env, jobject this, jobject dialog, jint which)
{
	(*env)->CallVoidMethod(env, this, J_get_method__DialogInterface__OnClickListener__onClick(env), dialog, which);
}

__attribute__((always_inline)) inline jclass J_get_class__Intent(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Intent.class))
		handle_cache.Intent.class = _REF((*env)->FindClass(env, "android/content/Intent"));

	return handle_cache.Intent.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Intent__constructor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Intent.constructor == 0))
		handle_cache.Intent.constructor = (*env)->GetMethodID(env, J_get_class__Intent(env), "<init>", "()V");

	return handle_cache.Intent.constructor;
}

__attribute__((always_inline)) inline jobject J_new__Intent(JNIEnv *env)
{
	jclass class = J_get_class__Intent(env);
	return (*env)->NewObject(env, class, J_get_method__Intent__constructor(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Intent__getDataString(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Intent.getDataString == 0))
		handle_cache.Intent.getDataString = (*env)->GetMethodID(env, J_get_class__Intent(env), "getDataString", "()Ljava/lang/String;");

	return handle_cache.Intent.getDataString;
}

__attribute__((always_inline)) inline jstring J__Intent__getDataString(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Intent__getDataString(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Intent__putExtraByteArray(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Intent.putExtraByteArray == 0))
		handle_cache.Intent.putExtraByteArray = (*env)->GetMethodID(env, J_get_class__Intent(env), "putExtra", "(Ljava/lang/String;[B)Landroid/content/Intent;");

	return handle_cache.Intent.putExtraByteArray;
}

__attribute__((always_inline)) inline jobject J__Intent__putExtraByteArray(JNIEnv *env, jobject this, jstring name, jbyteArray value)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Intent__putExtraByteArray(env), name, value);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Intent__putExtraCharSequence(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Intent.putExtraCharSequence == 0))
		handle_cache.Intent.putExtraCharSequence = (*env)->GetMethodID(env, J_get_class__Intent(env), "putExtra", "(Ljava/lang/String;Ljava/lang/CharSequence;)Landroid/content/Intent;");

	return handle_cache.Intent.putExtraCharSequence;
}

__attribute__((always_inline)) inline jobject J__Intent__putExtraCharSequence(JNIEnv *env, jobject this, jstring name, jobject value)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Intent__putExtraCharSequence(env), name, value);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Intent__putExtraInt(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Intent.putExtraInt == 0))
		handle_cache.Intent.putExtraInt = (*env)->GetMethodID(env, J_get_class__Intent(env), "putExtra", "(Ljava/lang/String;I)Landroid/content/Intent;");

	return handle_cache.Intent.putExtraInt;
}

__attribute__((always_inline)) inline jobject J__Intent__putExtraInt(JNIEnv *env, jobject this, jstring name, jint value)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Intent__putExtraInt(env), name, value);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Intent__putExtraLong(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Intent.putExtraLong == 0))
		handle_cache.Intent.putExtraLong = (*env)->GetMethodID(env, J_get_class__Intent(env), "putExtra", "(Ljava/lang/String;J)Landroid/content/Intent;");

	return handle_cache.Intent.putExtraLong;
}

__attribute__((always_inline)) inline jobject J__Intent__putExtraLong(JNIEnv *env, jobject this, jstring name, jlong value)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Intent__putExtraLong(env), name, value);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Intent__putExtraParcelable(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Intent.putExtraParcelable == 0))
		handle_cache.Intent.putExtraParcelable = (*env)->GetMethodID(env, J_get_class__Intent(env), "putExtra", "(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;");

	return handle_cache.Intent.putExtraParcelable;
}

__attribute__((always_inline)) inline jobject J__Intent__putExtraParcelable(JNIEnv *env, jobject this, jstring name, jobject value)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Intent__putExtraParcelable(env), name, value);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Intent__setClassName(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Intent.setClassName == 0))
		handle_cache.Intent.setClassName = (*env)->GetMethodID(env, J_get_class__Intent(env), "setClassName", "(Landroid/content/Context;Ljava/lang/String;)Landroid/content/Intent;");

	return handle_cache.Intent.setClassName;
}

__attribute__((always_inline)) inline jobject J__Intent__setClassName(JNIEnv *env, jobject this, jobject packageContext, jstring className)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Intent__setClassName(env), packageContext, className);
}

__attribute__((always_inline)) inline jclass J_get_class__AssetManager(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.AssetManager.class))
		handle_cache.AssetManager.class = _REF((*env)->FindClass(env, "android/content/res/AssetManager"));

	return handle_cache.AssetManager.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__AssetManager__extractFromAPK(JNIEnv *env)
{
	if (__unlikely__(handle_cache.AssetManager.extractFromAPK == 0))
		handle_cache.AssetManager.extractFromAPK = (*env)->GetStaticMethodID(env, J_get_class__AssetManager(env), "extractFromAPK", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

	return handle_cache.AssetManager.extractFromAPK;
}

__attribute__((always_inline)) inline void J__AssetManager__extractFromAPK(JNIEnv *env, jstring apk_resource_path, jstring path, jstring target)
{
	jclass class = J_get_class__AssetManager(env);
	return (*env)->CallStaticVoidMethod(env, class, J_get_method__AssetManager__extractFromAPK(env), apk_resource_path, path, target);
}

__attribute__((always_inline)) inline jclass J_get_class__SQLiteCustomFunction(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.SQLiteCustomFunction.class))
		handle_cache.SQLiteCustomFunction.class = _REF((*env)->FindClass(env, "android/database/sqlite/SQLiteCustomFunction"));

	return handle_cache.SQLiteCustomFunction.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__SQLiteCustomFunction__dispatchCallback(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SQLiteCustomFunction.dispatchCallback == 0))
		handle_cache.SQLiteCustomFunction.dispatchCallback = (*env)->GetMethodID(env, J_get_class__SQLiteCustomFunction(env), "dispatchCallback", "([Ljava/lang/String;)V");

	return handle_cache.SQLiteCustomFunction.dispatchCallback;
}

__attribute__((always_inline)) inline void J__SQLiteCustomFunction__dispatchCallback(JNIEnv *env, jobject this, jobjectArray args)
{
	(*env)->CallVoidMethod(env, this, J_get_method__SQLiteCustomFunction__dispatchCallback(env), args);
}

__attribute__((always_inline)) inline jclass J_get_class__Bitmap(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Bitmap.class))
		handle_cache.Bitmap.class = _REF((*env)->FindClass(env, "android/graphics/Bitmap"));

	return handle_cache.Bitmap.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Bitmap__getTexture(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Bitmap.getTexture == 0))
		handle_cache.Bitmap.getTexture = (*env)->GetMethodID(env, J_get_class__Bitmap(env), "getTexture", "()J");

	return handle_cache.Bitmap.getTexture;
}

__attribute__((always_inline)) inline jlong J__Bitmap__getTexture(JNIEnv *env, jobject this)
{
	return (*env)->CallLongMethod(env, this, J_get_method__Bitmap__getTexture(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Bitmap__recycle(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Bitmap.recycle == 0))
		handle_cache.Bitmap.recycle = (*env)->GetMethodID(env, J_get_class__Bitmap(env), "recycle", "()V");

	return handle_cache.Bitmap.recycle;
}

__attribute__((always_inline)) inline void J__Bitmap__recycle(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Bitmap__recycle(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Canvas(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Canvas.class))
		handle_cache.Canvas.class = _REF((*env)->FindClass(env, "android/graphics/Canvas"));

	return handle_cache.Canvas.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Canvas__drawText(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Canvas.drawText == 0))
		handle_cache.Canvas.drawText = (*env)->GetMethodID(env, J_get_class__Canvas(env), "drawText", "(Ljava/lang/CharSequence;IIFFLandroid/graphics/Paint;)V");

	return handle_cache.Canvas.drawText;
}

__attribute__((always_inline)) inline void J__Canvas__drawText(JNIEnv *env, jobject this, jobject text, jint start, jint end, jfloat x, jfloat y, jobject paint)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Canvas__drawText(env), text, start, end, x, y, paint);
}

__attribute__((always_inline)) inline jclass J_get_class__Paint(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Paint.class))
		handle_cache.Paint.class = _REF((*env)->FindClass(env, "android/graphics/Paint"));

	return handle_cache.Paint.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Paint__getColor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Paint.getColor == 0))
		handle_cache.Paint.getColor = (*env)->GetMethodID(env, J_get_class__Paint(env), "getColor", "()I");

	return handle_cache.Paint.getColor;
}

__attribute__((always_inline)) inline jint J__Paint__getColor(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__Paint__getColor(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Drawable(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Drawable.class))
		handle_cache.Drawable.class = _REF((*env)->FindClass(env, "android/graphics/drawable/Drawable"));

	return handle_cache.Drawable.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Drawable__draw(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Drawable.draw == 0))
		handle_cache.Drawable.draw = (*env)->GetMethodID(env, J_get_class__Drawable(env), "draw", "(Landroid/graphics/Canvas;)V");

	return handle_cache.Drawable.draw;
}

__attribute__((always_inline)) inline void J__Drawable__draw(JNIEnv *env, jobject this, jobject canvas)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Drawable__draw(env), canvas);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Drawable__getIntrinsicHeight(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Drawable.getIntrinsicHeight == 0))
		handle_cache.Drawable.getIntrinsicHeight = (*env)->GetMethodID(env, J_get_class__Drawable(env), "getIntrinsicHeight", "()I");

	return handle_cache.Drawable.getIntrinsicHeight;
}

__attribute__((always_inline)) inline jint J__Drawable__getIntrinsicHeight(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__Drawable__getIntrinsicHeight(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Drawable__getIntrinsicWidth(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Drawable.getIntrinsicWidth == 0))
		handle_cache.Drawable.getIntrinsicWidth = (*env)->GetMethodID(env, J_get_class__Drawable(env), "getIntrinsicWidth", "()I");

	return handle_cache.Drawable.getIntrinsicWidth;
}

__attribute__((always_inline)) inline jint J__Drawable__getIntrinsicWidth(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__Drawable__getIntrinsicWidth(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Drawable__setBounds(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Drawable.setBounds == 0))
		handle_cache.Drawable.setBounds = (*env)->GetMethodID(env, J_get_class__Drawable(env), "setBounds", "(IIII)V");

	return handle_cache.Drawable.setBounds;
}

__attribute__((always_inline)) inline void J__Drawable__setBounds(JNIEnv *env, jobject this, jint left, jint top, jint right, jint bottom)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Drawable__setBounds(env), left, top, right, bottom);
}

__attribute__((always_inline)) inline jclass J_get_class__SensorEvent(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.SensorEvent.class))
		handle_cache.SensorEvent.class = _REF((*env)->FindClass(env, "android/hardware/SensorEvent"));

	return handle_cache.SensorEvent.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__SensorEvent__constructor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SensorEvent.constructor == 0))
		handle_cache.SensorEvent.constructor = (*env)->GetMethodID(env, J_get_class__SensorEvent(env), "<init>", "([FLandroid/hardware/Sensor;)V");

	return handle_cache.SensorEvent.constructor;
}

__attribute__((always_inline)) inline jobject J_new__SensorEvent(JNIEnv *env, jfloatArray values, jobject sensor)
{
	jclass class = J_get_class__SensorEvent(env);
	return (*env)->NewObject(env, class, J_get_method__SensorEvent__constructor(env), values, sensor);
}

__attribute__((always_inline)) inline jclass J_get_class__SensorEventListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.SensorEventListener.class))
		handle_cache.SensorEventListener.class = _REF((*env)->FindClass(env, "android/hardware/SensorEventListener"));

	return handle_cache.SensorEventListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__SensorEventListener__onSensorChanged(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SensorEventListener.onSensorChanged == 0))
		handle_cache.SensorEventListener.onSensorChanged = (*env)->GetMethodID(env, J_get_class__SensorEventListener(env), "onSensorChanged", "(Landroid/hardware/SensorEvent;)V");

	return handle_cache.SensorEventListener.onSensorChanged;
}

__attribute__((always_inline)) inline void J__SensorEventListener__onSensorChanged(JNIEnv *env, jobject this, jobject event)
{
	(*env)->CallVoidMethod(env, this, J_get_method__SensorEventListener__onSensorChanged(env), event);
}

__attribute__((always_inline)) inline jclass J_get_class__LocationManager(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.LocationManager.class))
		handle_cache.LocationManager.class = _REF((*env)->FindClass(env, "android/location/LocationManager"));

	return handle_cache.LocationManager.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__LocationManager__locationUpdated(JNIEnv *env)
{
	if (__unlikely__(handle_cache.LocationManager.locationUpdated == 0))
		handle_cache.LocationManager.locationUpdated = (*env)->GetStaticMethodID(env, J_get_class__LocationManager(env), "locationUpdated", "(DDDDDDJ)V");

	return handle_cache.LocationManager.locationUpdated;
}

__attribute__((always_inline)) inline void J__LocationManager__locationUpdated(JNIEnv *env, jdouble latitude, jdouble longitude, jdouble altitude, jdouble accuracy, jdouble speed, jdouble bearing, jlong timestamp)
{
	jclass class = J_get_class__LocationManager(env);
	return (*env)->CallStaticVoidMethod(env, class, J_get_method__LocationManager__locationUpdated(env), latitude, longitude, altitude, accuracy, speed, bearing, timestamp);
}

__attribute__((always_inline)) inline jclass J_get_class__AudioTrack__OnPlaybackPositionUpdateListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.AudioTrack__OnPlaybackPositionUpdateListener.class))
		handle_cache.AudioTrack__OnPlaybackPositionUpdateListener.class = _REF((*env)->FindClass(env, "android/media/AudioTrack$OnPlaybackPositionUpdateListener"));

	return handle_cache.AudioTrack__OnPlaybackPositionUpdateListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__AudioTrack__OnPlaybackPositionUpdateListener__onPeriodicNotification(JNIEnv *env)
{
	if (__unlikely__(handle_cache.AudioTrack__OnPlaybackPositionUpdateListener.onPeriodicNotification == 0))
		handle_cache.AudioTrack__OnPlaybackPositionUpdateListener.onPeriodicNotification = (*env)->GetMethodID(env, J_get_class__AudioTrack__OnPlaybackPositionUpdateListener(env), "onPeriodicNotification", "(Landroid/media/AudioTrack;)V");

	return handle_cache.AudioTrack__OnPlaybackPositionUpdateListener.onPeriodicNotification;
}

__attribute__((always_inline)) inline void J__AudioTrack__OnPlaybackPositionUpdateListener__onPeriodicNotification(JNIEnv *env, jobject this, jobject track)
{
	(*env)->CallVoidMethod(env, this, J_get_method__AudioTrack__OnPlaybackPositionUpdateListener__onPeriodicNotification(env), track);
}

__attribute__((always_inline)) inline jclass J_get_class__MediaPlayer__OnCompletionListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.MediaPlayer__OnCompletionListener.class))
		handle_cache.MediaPlayer__OnCompletionListener.class = _REF((*env)->FindClass(env, "android/media/MediaPlayer$OnCompletionListener"));

	return handle_cache.MediaPlayer__OnCompletionListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__MediaPlayer__OnCompletionListener__onCompletion(JNIEnv *env)
{
	if (__unlikely__(handle_cache.MediaPlayer__OnCompletionListener.onCompletion == 0))
		handle_cache.MediaPlayer__OnCompletionListener.onCompletion = (*env)->GetMethodID(env, J_get_class__MediaPlayer__OnCompletionListener(env), "onCompletion", "(Landroid/media/MediaPlayer;)V");

	return handle_cache.MediaPlayer__OnCompletionListener.onCompletion;
}

__attribute__((always_inline)) inline void J__MediaPlayer__OnCompletionListener__onCompletion(JNIEnv *env, jobject this, jobject media_player)
{
	(*env)->CallVoidMethod(env, this, J_get_method__MediaPlayer__OnCompletionListener__onCompletion(env), media_player);
}

__attribute__((always_inline)) inline jclass J_get_class__MediaSession__Callback(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.MediaSession__Callback.class))
		handle_cache.MediaSession__Callback.class = _REF((*env)->FindClass(env, "android/media/session/MediaSession$Callback"));

	return handle_cache.MediaSession__Callback.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__MediaSession__Callback__onPause(JNIEnv *env)
{
	if (__unlikely__(handle_cache.MediaSession__Callback.onPause == 0))
		handle_cache.MediaSession__Callback.onPause = (*env)->GetMethodID(env, J_get_class__MediaSession__Callback(env), "onPause", "()V");

	return handle_cache.MediaSession__Callback.onPause;
}

__attribute__((always_inline)) inline void J__MediaSession__Callback__onPause(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__MediaSession__Callback__onPause(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__MediaSession__Callback__onPlay(JNIEnv *env)
{
	if (__unlikely__(handle_cache.MediaSession__Callback.onPlay == 0))
		handle_cache.MediaSession__Callback.onPlay = (*env)->GetMethodID(env, J_get_class__MediaSession__Callback(env), "onPlay", "()V");

	return handle_cache.MediaSession__Callback.onPlay;
}

__attribute__((always_inline)) inline void J__MediaSession__Callback__onPlay(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__MediaSession__Callback__onPlay(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__MediaSession__Callback__onSeekTo(JNIEnv *env)
{
	if (__unlikely__(handle_cache.MediaSession__Callback.onSeekTo == 0))
		handle_cache.MediaSession__Callback.onSeekTo = (*env)->GetMethodID(env, J_get_class__MediaSession__Callback(env), "onSeekTo", "(J)V");

	return handle_cache.MediaSession__Callback.onSeekTo;
}

__attribute__((always_inline)) inline void J__MediaSession__Callback__onSeekTo(JNIEnv *env, jobject this, jlong pos)
{
	(*env)->CallVoidMethod(env, this, J_get_method__MediaSession__Callback__onSeekTo(env), pos);
}

__attribute__((always_inline)) inline jclass J_get_class__ConnectivityManager__NetworkCallback(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.ConnectivityManager__NetworkCallback.class))
		handle_cache.ConnectivityManager__NetworkCallback.class = _REF((*env)->FindClass(env, "android/net/ConnectivityManager$NetworkCallback"));

	return handle_cache.ConnectivityManager__NetworkCallback.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__ConnectivityManager__NetworkCallback__onAvailable(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ConnectivityManager__NetworkCallback.onAvailable == 0))
		handle_cache.ConnectivityManager__NetworkCallback.onAvailable = (*env)->GetMethodID(env, J_get_class__ConnectivityManager__NetworkCallback(env), "onAvailable", "(Landroid/net/Network;)V");

	return handle_cache.ConnectivityManager__NetworkCallback.onAvailable;
}

__attribute__((always_inline)) inline void J__ConnectivityManager__NetworkCallback__onAvailable(JNIEnv *env, jobject this, jobject network)
{
	(*env)->CallVoidMethod(env, this, J_get_method__ConnectivityManager__NetworkCallback__onAvailable(env), network);
}

__attribute__((always_inline)) inline jmethodID J_get_method__ConnectivityManager__NetworkCallback__onLost(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ConnectivityManager__NetworkCallback.onLost == 0))
		handle_cache.ConnectivityManager__NetworkCallback.onLost = (*env)->GetMethodID(env, J_get_class__ConnectivityManager__NetworkCallback(env), "onLost", "(Landroid/net/Network;)V");

	return handle_cache.ConnectivityManager__NetworkCallback.onLost;
}

__attribute__((always_inline)) inline void J__ConnectivityManager__NetworkCallback__onLost(JNIEnv *env, jobject this, jobject network)
{
	(*env)->CallVoidMethod(env, this, J_get_method__ConnectivityManager__NetworkCallback__onLost(env), network);
}

__attribute__((always_inline)) inline jclass J_get_class__Uri(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Uri.class))
		handle_cache.Uri.class = _REF((*env)->FindClass(env, "android/net/Uri"));

	return handle_cache.Uri.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Uri__parse(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Uri.parse == 0))
		handle_cache.Uri.parse = (*env)->GetStaticMethodID(env, J_get_class__Uri(env), "parse", "(Ljava/lang/String;)Landroid/net/Uri;");

	return handle_cache.Uri.parse;
}

__attribute__((always_inline)) inline jobject J__Uri__parse(JNIEnv *env, jstring uriString)
{
	jclass class = J_get_class__Uri(env);
	return (*env)->CallStaticObjectMethod(env, class, J_get_method__Uri__parse(env), uriString);
}

__attribute__((always_inline)) inline jclass J_get_class__BaseBundle(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.BaseBundle.class))
		handle_cache.BaseBundle.class = _REF((*env)->FindClass(env, "android/os/BaseBundle"));

	return handle_cache.BaseBundle.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__BaseBundle__get(JNIEnv *env)
{
	if (__unlikely__(handle_cache.BaseBundle.get == 0))
		handle_cache.BaseBundle.get = (*env)->GetMethodID(env, J_get_class__BaseBundle(env), "get", "(Ljava/lang/String;)Ljava/lang/Object;");

	return handle_cache.BaseBundle.get;
}

__attribute__((always_inline)) inline jobject J__BaseBundle__get(JNIEnv *env, jobject this, jstring key)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__BaseBundle__get(env), key);
}

__attribute__((always_inline)) inline jmethodID J_get_method__BaseBundle__keySet(JNIEnv *env)
{
	if (__unlikely__(handle_cache.BaseBundle.keySet == 0))
		handle_cache.BaseBundle.keySet = (*env)->GetMethodID(env, J_get_class__BaseBundle(env), "keySet", "()Ljava/util/Set;");

	return handle_cache.BaseBundle.keySet;
}

__attribute__((always_inline)) inline jobject J__BaseBundle__keySet(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__BaseBundle__keySet(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Looper(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Looper.class))
		handle_cache.Looper.class = _REF((*env)->FindClass(env, "android/os/Looper"));

	return handle_cache.Looper.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Looper__loop(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Looper.loop == 0))
		handle_cache.Looper.loop = (*env)->GetStaticMethodID(env, J_get_class__Looper(env), "loop", "()V");

	return handle_cache.Looper.loop;
}

__attribute__((always_inline)) inline void J__Looper__loop(JNIEnv *env)
{
	jclass class = J_get_class__Looper(env);
	return (*env)->CallStaticVoidMethod(env, class, J_get_method__Looper__loop(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Looper__prepareMainLooper(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Looper.prepareMainLooper == 0))
		handle_cache.Looper.prepareMainLooper = (*env)->GetStaticMethodID(env, J_get_class__Looper(env), "prepareMainLooper", "()V");

	return handle_cache.Looper.prepareMainLooper;
}

__attribute__((always_inline)) inline void J__Looper__prepareMainLooper(JNIEnv *env)
{
	jclass class = J_get_class__Looper(env);
	return (*env)->CallStaticVoidMethod(env, class, J_get_method__Looper__prepareMainLooper(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Parcel(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Parcel.class))
		handle_cache.Parcel.class = _REF((*env)->FindClass(env, "android/os/Parcel"));

	return handle_cache.Parcel.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Parcel__readParcelable(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Parcel.readParcelable == 0))
		handle_cache.Parcel.readParcelable = (*env)->GetMethodID(env, J_get_class__Parcel(env), "readParcelable", "(Ljava/lang/ClassLoader;)Landroid/os/Parcelable;");

	return handle_cache.Parcel.readParcelable;
}

__attribute__((always_inline)) inline jobject J__Parcel__readParcelable(JNIEnv *env, jobject this, jobject loader)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Parcel__readParcelable(env), loader);
}

__attribute__((always_inline)) inline jmethodID J_get_method__Parcel__writeParcelable(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Parcel.writeParcelable == 0))
		handle_cache.Parcel.writeParcelable = (*env)->GetMethodID(env, J_get_class__Parcel(env), "writeParcelable", "(Landroid/os/Parcelable;I)V");

	return handle_cache.Parcel.writeParcelable;
}

__attribute__((always_inline)) inline void J__Parcel__writeParcelable(JNIEnv *env, jobject this, jobject p, jint flags)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Parcel__writeParcelable(env), p, flags);
}

__attribute__((always_inline)) inline jclass J_get_class__SpannableStringBuilder(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.SpannableStringBuilder.class))
		handle_cache.SpannableStringBuilder.class = _REF((*env)->FindClass(env, "android/text/SpannableStringBuilder"));

	return handle_cache.SpannableStringBuilder.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__SpannableStringBuilder__constructor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SpannableStringBuilder.constructor == 0))
		handle_cache.SpannableStringBuilder.constructor = (*env)->GetMethodID(env, J_get_class__SpannableStringBuilder(env), "<init>", "(Ljava/lang/CharSequence;)V");

	return handle_cache.SpannableStringBuilder.constructor;
}

__attribute__((always_inline)) inline jobject J_new__SpannableStringBuilder(JNIEnv *env, jobject text)
{
	jclass class = J_get_class__SpannableStringBuilder(env);
	return (*env)->NewObject(env, class, J_get_method__SpannableStringBuilder__constructor(env), text);
}

__attribute__((always_inline)) inline jclass J_get_class__TextWatcher(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.TextWatcher.class))
		handle_cache.TextWatcher.class = _REF((*env)->FindClass(env, "android/text/TextWatcher"));

	return handle_cache.TextWatcher.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__TextWatcher__afterTextChanged(JNIEnv *env)
{
	if (__unlikely__(handle_cache.TextWatcher.afterTextChanged == 0))
		handle_cache.TextWatcher.afterTextChanged = (*env)->GetMethodID(env, J_get_class__TextWatcher(env), "afterTextChanged", "(Landroid/text/Editable;)V");

	return handle_cache.TextWatcher.afterTextChanged;
}

__attribute__((always_inline)) inline void J__TextWatcher__afterTextChanged(JNIEnv *env, jobject this, jobject s)
{
	(*env)->CallVoidMethod(env, this, J_get_method__TextWatcher__afterTextChanged(env), s);
}

__attribute__((always_inline)) inline jmethodID J_get_method__TextWatcher__onTextChanged(JNIEnv *env)
{
	if (__unlikely__(handle_cache.TextWatcher.onTextChanged == 0))
		handle_cache.TextWatcher.onTextChanged = (*env)->GetMethodID(env, J_get_class__TextWatcher(env), "onTextChanged", "(Ljava/lang/CharSequence;III)V");

	return handle_cache.TextWatcher.onTextChanged;
}

__attribute__((always_inline)) inline void J__TextWatcher__onTextChanged(JNIEnv *env, jobject this, jobject s, jint start, jint before, jint count)
{
	(*env)->CallVoidMethod(env, this, J_get_method__TextWatcher__onTextChanged(env), s, start, before, count);
}

__attribute__((always_inline)) inline jclass J_get_class__AttributeSet(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.AttributeSet.class))
		handle_cache.AttributeSet.class = _REF((*env)->FindClass(env, "android/util/AttributeSet"));

	return handle_cache.AttributeSet.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__AttributeSet__getAttributeIntValue(JNIEnv *env)
{
	if (__unlikely__(handle_cache.AttributeSet.getAttributeIntValue == 0))
		handle_cache.AttributeSet.getAttributeIntValue = (*env)->GetMethodID(env, J_get_class__AttributeSet(env), "getAttributeIntValue", "(Ljava/lang/String;Ljava/lang/String;I)I");

	return handle_cache.AttributeSet.getAttributeIntValue;
}

__attribute__((always_inline)) inline jint J__AttributeSet__getAttributeIntValue(JNIEnv *env, jobject this, jstring namespace, jstring attribute, jint defaultValue)
{
	return (*env)->CallIntMethod(env, this, J_get_method__AttributeSet__getAttributeIntValue(env), namespace, attribute, defaultValue);
}

__attribute__((always_inline)) inline jmethodID J_get_method__AttributeSet__getAttributeValue(JNIEnv *env)
{
	if (__unlikely__(handle_cache.AttributeSet.getAttributeValue == 0))
		handle_cache.AttributeSet.getAttributeValue = (*env)->GetMethodID(env, J_get_class__AttributeSet(env), "getAttributeValue", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");

	return handle_cache.AttributeSet.getAttributeValue;
}

__attribute__((always_inline)) inline jstring J__AttributeSet__getAttributeValue(JNIEnv *env, jobject this, jstring namespace, jstring name)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__AttributeSet__getAttributeValue(env), namespace, name);
}

__attribute__((always_inline)) inline jclass J_get_class__InputQueue__Callback(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.InputQueue__Callback.class))
		handle_cache.InputQueue__Callback.class = _REF((*env)->FindClass(env, "android/view/InputQueue$Callback"));

	return handle_cache.InputQueue__Callback.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__InputQueue__Callback__onInputQueueCreated(JNIEnv *env)
{
	if (__unlikely__(handle_cache.InputQueue__Callback.onInputQueueCreated == 0))
		handle_cache.InputQueue__Callback.onInputQueueCreated = (*env)->GetMethodID(env, J_get_class__InputQueue__Callback(env), "onInputQueueCreated", "(Landroid/view/InputQueue;)V");

	return handle_cache.InputQueue__Callback.onInputQueueCreated;
}

__attribute__((always_inline)) inline void J__InputQueue__Callback__onInputQueueCreated(JNIEnv *env, jobject this, jobject queue)
{
	(*env)->CallVoidMethod(env, this, J_get_method__InputQueue__Callback__onInputQueueCreated(env), queue);
}

__attribute__((always_inline)) inline jclass J_get_class__KeyEvent(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.KeyEvent.class))
		handle_cache.KeyEvent.class = _REF((*env)->FindClass(env, "android/view/KeyEvent"));

	return handle_cache.KeyEvent.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__KeyEvent__constructor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.KeyEvent.constructor == 0))
		handle_cache.KeyEvent.constructor = (*env)->GetMethodID(env, J_get_class__KeyEvent(env), "<init>", "(JJIIII)V");

	return handle_cache.KeyEvent.constructor;
}

__attribute__((always_inline)) inline jobject J_new__KeyEvent(JNIEnv *env, jlong downTime, jlong eventTime, jint action, jint code, jint repeat, jint metaState)
{
	jclass class = J_get_class__KeyEvent(env);
	return (*env)->NewObject(env, class, J_get_method__KeyEvent__constructor(env), downTime, eventTime, action, code, repeat, metaState);
}

__attribute__((always_inline)) inline jclass J_get_class__MotionEvent(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.MotionEvent.class))
		handle_cache.MotionEvent.class = _REF((*env)->FindClass(env, "android/view/MotionEvent"));

	return handle_cache.MotionEvent.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__MotionEvent__constructor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.MotionEvent.constructor == 0))
		handle_cache.MotionEvent.constructor = (*env)->GetMethodID(env, J_get_class__MotionEvent(env), "<init>", "(IIJ[I[F)V");

	return handle_cache.MotionEvent.constructor;
}

__attribute__((always_inline)) inline jobject J_new__MotionEvent(JNIEnv *env, jint source, jint action, jlong eventTime, jintArray ids, jfloatArray coords)
{
	jclass class = J_get_class__MotionEvent(env);
	return (*env)->NewObject(env, class, J_get_method__MotionEvent__constructor(env), source, action, eventTime, ids, coords);
}

__attribute__((always_inline)) inline jmethodID J_get_method__MotionEvent__constructor_scroll(JNIEnv *env)
{
	if (__unlikely__(handle_cache.MotionEvent.constructor_scroll == 0))
		handle_cache.MotionEvent.constructor_scroll = (*env)->GetMethodID(env, J_get_class__MotionEvent(env), "<init>", "(IIJFFFFFF)V");

	return handle_cache.MotionEvent.constructor_scroll;
}

__attribute__((always_inline)) inline jobject J_new__MotionEvent__scroll(JNIEnv *env, jint source, jint action, jlong eventTime, jfloat x, jfloat y, jfloat raw_x, jfloat raw_y, jfloat scroll_dx, jfloat scroll_dy)
{
	jclass class = J_get_class__MotionEvent(env);
	return (*env)->NewObject(env, class, J_get_method__MotionEvent__constructor_scroll(env), source, action, eventTime, x, y, raw_x, raw_y, scroll_dx, scroll_dy);
}

__attribute__((always_inline)) inline jmethodID J_get_method__MotionEvent__constructor_single(JNIEnv *env)
{
	if (__unlikely__(handle_cache.MotionEvent.constructor_single == 0))
		handle_cache.MotionEvent.constructor_single = (*env)->GetMethodID(env, J_get_class__MotionEvent(env), "<init>", "(IIJFFFF)V");

	return handle_cache.MotionEvent.constructor_single;
}

__attribute__((always_inline)) inline jobject J_new__MotionEvent__single(JNIEnv *env, jint source, jint action, jlong eventTime, jfloat x, jfloat y, jfloat raw_x, jfloat raw_y)
{
	jclass class = J_get_class__MotionEvent(env);
	return (*env)->NewObject(env, class, J_get_method__MotionEvent__constructor_single(env), source, action, eventTime, x, y, raw_x, raw_y);
}

__attribute__((always_inline)) inline jclass J_get_class__SurfaceView(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.SurfaceView.class))
		handle_cache.SurfaceView.class = _REF((*env)->FindClass(env, "android/view/SurfaceView"));

	return handle_cache.SurfaceView.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__SurfaceView__surfaceChanged(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SurfaceView.surfaceChanged == 0))
		handle_cache.SurfaceView.surfaceChanged = (*env)->GetMethodID(env, J_get_class__SurfaceView(env), "surfaceChanged", "(III)V");

	return handle_cache.SurfaceView.surfaceChanged;
}

__attribute__((always_inline)) inline void J__SurfaceView__surfaceChanged(JNIEnv *env, jobject this, jint format, jint width, jint height)
{
	(*env)->CallVoidMethod(env, this, J_get_method__SurfaceView__surfaceChanged(env), format, width, height);
}

__attribute__((always_inline)) inline jmethodID J_get_method__SurfaceView__surfaceCreated(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SurfaceView.surfaceCreated == 0))
		handle_cache.SurfaceView.surfaceCreated = (*env)->GetMethodID(env, J_get_class__SurfaceView(env), "surfaceCreated", "()V");

	return handle_cache.SurfaceView.surfaceCreated;
}

__attribute__((always_inline)) inline void J__SurfaceView__surfaceCreated(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__SurfaceView__surfaceCreated(env));
}

__attribute__((always_inline)) inline jclass J_get_class__View(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.View.class))
		handle_cache.View.class = _REF((*env)->FindClass(env, "android/view/View"));

	return handle_cache.View.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__computeScroll(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.computeScroll == 0))
		handle_cache.View.computeScroll = (*env)->GetMethodID(env, J_get_class__View(env), "computeScroll", "()V");

	return handle_cache.View.computeScroll;
}

__attribute__((always_inline)) inline void J__View__computeScroll(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__computeScroll(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__dispatchDraw(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.dispatchDraw == 0))
		handle_cache.View.dispatchDraw = (*env)->GetMethodID(env, J_get_class__View(env), "dispatchDraw", "(Landroid/graphics/Canvas;)V");

	return handle_cache.View.dispatchDraw;
}

__attribute__((always_inline)) inline void J__View__dispatchDraw(JNIEnv *env, jobject this, jobject canvas)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__dispatchDraw(env), canvas);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__dispatchGenericMotionEvent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.dispatchGenericMotionEvent == 0))
		handle_cache.View.dispatchGenericMotionEvent = (*env)->GetMethodID(env, J_get_class__View(env), "dispatchGenericMotionEvent", "(Landroid/view/MotionEvent;)Z");

	return handle_cache.View.dispatchGenericMotionEvent;
}

__attribute__((always_inline)) inline jboolean J__View__dispatchGenericMotionEvent(JNIEnv *env, jobject this, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__dispatchGenericMotionEvent(env), event);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__dispatchHoverEvent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.dispatchHoverEvent == 0))
		handle_cache.View.dispatchHoverEvent = (*env)->GetMethodID(env, J_get_class__View(env), "dispatchHoverEvent", "(Landroid/view/MotionEvent;)Z");

	return handle_cache.View.dispatchHoverEvent;
}

__attribute__((always_inline)) inline jboolean J__View__dispatchHoverEvent(JNIEnv *env, jobject this, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__dispatchHoverEvent(env), event);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__dispatchKeyEvent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.dispatchKeyEvent == 0))
		handle_cache.View.dispatchKeyEvent = (*env)->GetMethodID(env, J_get_class__View(env), "dispatchKeyEvent", "(Landroid/view/KeyEvent;)Z");

	return handle_cache.View.dispatchKeyEvent;
}

__attribute__((always_inline)) inline jboolean J__View__dispatchKeyEvent(JNIEnv *env, jobject this, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__dispatchKeyEvent(env), event);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__dispatchTouchEvent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.dispatchTouchEvent == 0))
		handle_cache.View.dispatchTouchEvent = (*env)->GetMethodID(env, J_get_class__View(env), "dispatchTouchEvent", "(Landroid/view/MotionEvent;)Z");

	return handle_cache.View.dispatchTouchEvent;
}

__attribute__((always_inline)) inline jboolean J__View__dispatchTouchEvent(JNIEnv *env, jobject this, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__dispatchTouchEvent(env), event);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__draw(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.draw == 0))
		handle_cache.View.draw = (*env)->GetMethodID(env, J_get_class__View(env), "draw", "(Landroid/graphics/Canvas;)V");

	return handle_cache.View.draw;
}

__attribute__((always_inline)) inline void J__View__draw(JNIEnv *env, jobject this, jobject canvas)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__draw(env), canvas);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getAllSuperClasses(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getAllSuperClasses == 0))
		handle_cache.View.getAllSuperClasses = (*env)->GetMethodID(env, J_get_class__View(env), "getAllSuperClasses", "()Ljava/lang/String;");

	return handle_cache.View.getAllSuperClasses;
}

__attribute__((always_inline)) inline jstring J__View__getAllSuperClasses(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__View__getAllSuperClasses(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getId(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getId == 0))
		handle_cache.View.getId = (*env)->GetMethodID(env, J_get_class__View(env), "getId", "()I");

	return handle_cache.View.getId;
}

__attribute__((always_inline)) inline jint J__View__getId(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__View__getId(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getIdName(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getIdName == 0))
		handle_cache.View.getIdName = (*env)->GetMethodID(env, J_get_class__View(env), "getIdName", "()Ljava/lang/String;");

	return handle_cache.View.getIdName;
}

__attribute__((always_inline)) inline jstring J__View__getIdName(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__View__getIdName(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getMeasuredHeight(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getMeasuredHeight == 0))
		handle_cache.View.getMeasuredHeight = (*env)->GetMethodID(env, J_get_class__View(env), "getMeasuredHeight", "()I");

	return handle_cache.View.getMeasuredHeight;
}

__attribute__((always_inline)) inline jint J__View__getMeasuredHeight(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__View__getMeasuredHeight(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getMeasuredWidth(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getMeasuredWidth == 0))
		handle_cache.View.getMeasuredWidth = (*env)->GetMethodID(env, J_get_class__View(env), "getMeasuredWidth", "()I");

	return handle_cache.View.getMeasuredWidth;
}

__attribute__((always_inline)) inline jint J__View__getMeasuredWidth(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__View__getMeasuredWidth(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getScrollX(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getScrollX == 0))
		handle_cache.View.getScrollX = (*env)->GetMethodID(env, J_get_class__View(env), "getScrollX", "()I");

	return handle_cache.View.getScrollX;
}

__attribute__((always_inline)) inline jint J__View__getScrollX(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__View__getScrollX(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getScrollY(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getScrollY == 0))
		handle_cache.View.getScrollY = (*env)->GetMethodID(env, J_get_class__View(env), "getScrollY", "()I");

	return handle_cache.View.getScrollY;
}

__attribute__((always_inline)) inline jint J__View__getScrollY(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__View__getScrollY(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getSuggestedMinimumHeight(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getSuggestedMinimumHeight == 0))
		handle_cache.View.getSuggestedMinimumHeight = (*env)->GetMethodID(env, J_get_class__View(env), "getSuggestedMinimumHeight", "()I");

	return handle_cache.View.getSuggestedMinimumHeight;
}

__attribute__((always_inline)) inline jint J__View__getSuggestedMinimumHeight(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__View__getSuggestedMinimumHeight(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__getSuggestedMinimumWidth(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.getSuggestedMinimumWidth == 0))
		handle_cache.View.getSuggestedMinimumWidth = (*env)->GetMethodID(env, J_get_class__View(env), "getSuggestedMinimumWidth", "()I");

	return handle_cache.View.getSuggestedMinimumWidth;
}

__attribute__((always_inline)) inline jint J__View__getSuggestedMinimumWidth(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__View__getSuggestedMinimumWidth(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__layoutInternal(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.layoutInternal == 0))
		handle_cache.View.layoutInternal = (*env)->GetMethodID(env, J_get_class__View(env), "layoutInternal", "(II)V");

	return handle_cache.View.layoutInternal;
}

__attribute__((always_inline)) inline void J__View__layoutInternal(JNIEnv *env, jobject this, jint width, jint height)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__layoutInternal(env), width, height);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__measure(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.measure == 0))
		handle_cache.View.measure = (*env)->GetMethodID(env, J_get_class__View(env), "measure", "(II)V");

	return handle_cache.View.measure;
}

__attribute__((always_inline)) inline void J__View__measure(JNIEnv *env, jobject this, jint widthMeasureSpec, jint heightMeasureSpec)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__measure(env), widthMeasureSpec, heightMeasureSpec);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onAttachedToWindow(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onAttachedToWindow == 0))
		handle_cache.View.onAttachedToWindow = (*env)->GetMethodID(env, J_get_class__View(env), "onAttachedToWindow", "()V");

	return handle_cache.View.onAttachedToWindow;
}

__attribute__((always_inline)) inline void J__View__onAttachedToWindow(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__onAttachedToWindow(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onDetachedFromWindow(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onDetachedFromWindow == 0))
		handle_cache.View.onDetachedFromWindow = (*env)->GetMethodID(env, J_get_class__View(env), "onDetachedFromWindow", "()V");

	return handle_cache.View.onDetachedFromWindow;
}

__attribute__((always_inline)) inline void J__View__onDetachedFromWindow(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__onDetachedFromWindow(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onDraw(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onDraw == 0))
		handle_cache.View.onDraw = (*env)->GetMethodID(env, J_get_class__View(env), "onDraw", "(Landroid/graphics/Canvas;)V");

	return handle_cache.View.onDraw;
}

__attribute__((always_inline)) inline void J__View__onDraw(JNIEnv *env, jobject this, jobject canvas)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__onDraw(env), canvas);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onGenericMotionEvent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onGenericMotionEvent == 0))
		handle_cache.View.onGenericMotionEvent = (*env)->GetMethodID(env, J_get_class__View(env), "onGenericMotionEvent", "(Landroid/view/MotionEvent;)Z");

	return handle_cache.View.onGenericMotionEvent;
}

__attribute__((always_inline)) inline jboolean J__View__onGenericMotionEvent(JNIEnv *env, jobject this, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__onGenericMotionEvent(env), event);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onInterceptTouchEvent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onInterceptTouchEvent == 0))
		handle_cache.View.onInterceptTouchEvent = (*env)->GetMethodID(env, J_get_class__View(env), "onInterceptTouchEvent", "(Landroid/view/MotionEvent;)Z");

	return handle_cache.View.onInterceptTouchEvent;
}

__attribute__((always_inline)) inline jboolean J__View__onInterceptTouchEvent(JNIEnv *env, jobject this, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__onInterceptTouchEvent(env), event);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onKeyDown(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onKeyDown == 0))
		handle_cache.View.onKeyDown = (*env)->GetMethodID(env, J_get_class__View(env), "onKeyDown", "(ILandroid/view/KeyEvent;)Z");

	return handle_cache.View.onKeyDown;
}

__attribute__((always_inline)) inline jboolean J__View__onKeyDown(JNIEnv *env, jobject this, jint keyCode, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__onKeyDown(env), keyCode, event);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onLayout(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onLayout == 0))
		handle_cache.View.onLayout = (*env)->GetMethodID(env, J_get_class__View(env), "onLayout", "(ZIIII)V");

	return handle_cache.View.onLayout;
}

__attribute__((always_inline)) inline void J__View__onLayout(JNIEnv *env, jobject this, jboolean changed, jint l, jint t, jint r, jint b)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__onLayout(env), changed, l, t, r, b);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onMeasure(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onMeasure == 0))
		handle_cache.View.onMeasure = (*env)->GetMethodID(env, J_get_class__View(env), "onMeasure", "(II)V");

	return handle_cache.View.onMeasure;
}

__attribute__((always_inline)) inline void J__View__onMeasure(JNIEnv *env, jobject this, jint widthMeasureSpec, jint heightMeasureSpec)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__onMeasure(env), widthMeasureSpec, heightMeasureSpec);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onTouchEvent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onTouchEvent == 0))
		handle_cache.View.onTouchEvent = (*env)->GetMethodID(env, J_get_class__View(env), "onTouchEvent", "(Landroid/view/MotionEvent;)Z");

	return handle_cache.View.onTouchEvent;
}

__attribute__((always_inline)) inline jboolean J__View__onTouchEvent(JNIEnv *env, jobject this, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__onTouchEvent(env), event);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__onTouchEventInternal(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.onTouchEventInternal == 0))
		handle_cache.View.onTouchEventInternal = (*env)->GetMethodID(env, J_get_class__View(env), "onTouchEventInternal", "(Landroid/view/MotionEvent;Z)Z");

	return handle_cache.View.onTouchEventInternal;
}

__attribute__((always_inline)) inline jboolean J__View__onTouchEventInternal(JNIEnv *env, jobject this, jobject event, jboolean handle_gestures)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__onTouchEventInternal(env), event, handle_gestures);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__performClick(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.performClick == 0))
		handle_cache.View.performClick = (*env)->GetMethodID(env, J_get_class__View(env), "performClick", "()Z");

	return handle_cache.View.performClick;
}

__attribute__((always_inline)) inline jboolean J__View__performClick(JNIEnv *env, jobject this)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__performClick(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__performLongClick(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.performLongClick == 0))
		handle_cache.View.performLongClick = (*env)->GetMethodID(env, J_get_class__View(env), "performLongClick", "(FF)Z");

	return handle_cache.View.performLongClick;
}

__attribute__((always_inline)) inline jboolean J__View__performLongClick(JNIEnv *env, jobject this, jfloat x, jfloat y)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__View__performLongClick(env), x, y);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__setLayoutParams(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.setLayoutParams == 0))
		handle_cache.View.setLayoutParams = (*env)->GetMethodID(env, J_get_class__View(env), "setLayoutParams", "(Landroid/view/ViewGroup$LayoutParams;)V");

	return handle_cache.View.setLayoutParams;
}

__attribute__((always_inline)) inline void J__View__setLayoutParams(JNIEnv *env, jobject this, jobject params)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__setLayoutParams(env), params);
}

__attribute__((always_inline)) inline jmethodID J_get_method__View__setMeasuredDimension(JNIEnv *env)
{
	if (__unlikely__(handle_cache.View.setMeasuredDimension == 0))
		handle_cache.View.setMeasuredDimension = (*env)->GetMethodID(env, J_get_class__View(env), "setMeasuredDimension", "(II)V");

	return handle_cache.View.setMeasuredDimension;
}

__attribute__((always_inline)) inline void J__View__setMeasuredDimension(JNIEnv *env, jobject this, jint measuredWidth, jint measuredHeight)
{
	(*env)->CallVoidMethod(env, this, J_get_method__View__setMeasuredDimension(env), measuredWidth, measuredHeight);
}

__attribute__((always_inline)) inline jclass J_get_class__ViewGroup(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.ViewGroup.class))
		handle_cache.ViewGroup.class = _REF((*env)->FindClass(env, "android/view/ViewGroup"));

	return handle_cache.ViewGroup.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__ViewGroup__dispatchTouchEvent(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ViewGroup.dispatchTouchEvent == 0))
		handle_cache.ViewGroup.dispatchTouchEvent = (*env)->GetMethodID(env, J_get_class__ViewGroup(env), "dispatchTouchEvent", "(Landroid/view/MotionEvent;)Z");

	return handle_cache.ViewGroup.dispatchTouchEvent;
}

__attribute__((always_inline)) inline jboolean J__ViewGroup__dispatchTouchEvent(JNIEnv *env, jobject this, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__ViewGroup__dispatchTouchEvent(env), event);
}

__attribute__((always_inline)) inline jclass J_get_class__ViewTreeObserver(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.ViewTreeObserver.class))
		handle_cache.ViewTreeObserver.class = _REF((*env)->FindClass(env, "android/view/ViewTreeObserver"));

	return handle_cache.ViewTreeObserver.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__ViewTreeObserver__dispatchOnGlobalLayout(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ViewTreeObserver.dispatchOnGlobalLayout == 0))
		handle_cache.ViewTreeObserver.dispatchOnGlobalLayout = (*env)->GetMethodID(env, J_get_class__ViewTreeObserver(env), "dispatchOnGlobalLayout", "()V");

	return handle_cache.ViewTreeObserver.dispatchOnGlobalLayout;
}

__attribute__((always_inline)) inline void J__ViewTreeObserver__dispatchOnGlobalLayout(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__ViewTreeObserver__dispatchOnGlobalLayout(env));
}

__attribute__((always_inline)) inline jclass J_get_class__InputConnection(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.InputConnection.class))
		handle_cache.InputConnection.class = _REF((*env)->FindClass(env, "android/view/inputmethod/InputConnection"));

	return handle_cache.InputConnection.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__InputConnection__commitText(JNIEnv *env)
{
	if (__unlikely__(handle_cache.InputConnection.commitText == 0))
		handle_cache.InputConnection.commitText = (*env)->GetMethodID(env, J_get_class__InputConnection(env), "commitText", "(Ljava/lang/CharSequence;I)Z");

	return handle_cache.InputConnection.commitText;
}

__attribute__((always_inline)) inline jboolean J__InputConnection__commitText(JNIEnv *env, jobject this, jobject text, jint newCursorPosition)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__InputConnection__commitText(env), text, newCursorPosition);
}

__attribute__((always_inline)) inline jmethodID J_get_method__InputConnection__deleteSurroundingText(JNIEnv *env)
{
	if (__unlikely__(handle_cache.InputConnection.deleteSurroundingText == 0))
		handle_cache.InputConnection.deleteSurroundingText = (*env)->GetMethodID(env, J_get_class__InputConnection(env), "deleteSurroundingText", "(II)Z");

	return handle_cache.InputConnection.deleteSurroundingText;
}

__attribute__((always_inline)) inline jboolean J__InputConnection__deleteSurroundingText(JNIEnv *env, jobject this, jint beforeLength, jint afterLength)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__InputConnection__deleteSurroundingText(env), beforeLength, afterLength);
}

__attribute__((always_inline)) inline jmethodID J_get_method__InputConnection__getTextAfterCursor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.InputConnection.getTextAfterCursor == 0))
		handle_cache.InputConnection.getTextAfterCursor = (*env)->GetMethodID(env, J_get_class__InputConnection(env), "getTextAfterCursor", "(II)Ljava/lang/CharSequence;");

	return handle_cache.InputConnection.getTextAfterCursor;
}

__attribute__((always_inline)) inline jobject J__InputConnection__getTextAfterCursor(JNIEnv *env, jobject this, jint n, jint flags)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__InputConnection__getTextAfterCursor(env), n, flags);
}

__attribute__((always_inline)) inline jmethodID J_get_method__InputConnection__getTextBeforeCursor(JNIEnv *env)
{
	if (__unlikely__(handle_cache.InputConnection.getTextBeforeCursor == 0))
		handle_cache.InputConnection.getTextBeforeCursor = (*env)->GetMethodID(env, J_get_class__InputConnection(env), "getTextBeforeCursor", "(II)Ljava/lang/CharSequence;");

	return handle_cache.InputConnection.getTextBeforeCursor;
}

__attribute__((always_inline)) inline jobject J__InputConnection__getTextBeforeCursor(JNIEnv *env, jobject this, jint n, jint flags)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__InputConnection__getTextBeforeCursor(env), n, flags);
}

__attribute__((always_inline)) inline jclass J_get_class__WebView(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.WebView.class))
		handle_cache.WebView.class = _REF((*env)->FindClass(env, "android/webkit/WebView"));

	return handle_cache.WebView.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__WebView__internalGetAssetManager(JNIEnv *env)
{
	if (__unlikely__(handle_cache.WebView.internalGetAssetManager == 0))
		handle_cache.WebView.internalGetAssetManager = (*env)->GetMethodID(env, J_get_class__WebView(env), "internalGetAssetManager", "()Landroid/content/res/AssetManager;");

	return handle_cache.WebView.internalGetAssetManager;
}

__attribute__((always_inline)) inline jobject J__WebView__internalGetAssetManager(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__WebView__internalGetAssetManager(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__WebView__internalLoadChanged(JNIEnv *env)
{
	if (__unlikely__(handle_cache.WebView.internalLoadChanged == 0))
		handle_cache.WebView.internalLoadChanged = (*env)->GetMethodID(env, J_get_class__WebView(env), "internalLoadChanged", "(ILjava/lang/String;)V");

	return handle_cache.WebView.internalLoadChanged;
}

__attribute__((always_inline)) inline void J__WebView__internalLoadChanged(JNIEnv *env, jobject this, jint loadState, jstring url)
{
	(*env)->CallVoidMethod(env, this, J_get_method__WebView__internalLoadChanged(env), loadState, url);
}

__attribute__((always_inline)) inline jclass J_get_class__Adapter(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Adapter.class))
		handle_cache.Adapter.class = _REF((*env)->FindClass(env, "android/widget/Adapter"));

	return handle_cache.Adapter.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Adapter__getCount(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Adapter.getCount == 0))
		handle_cache.Adapter.getCount = (*env)->GetMethodID(env, J_get_class__Adapter(env), "getCount", "()I");

	return handle_cache.Adapter.getCount;
}

__attribute__((always_inline)) inline jint J__Adapter__getCount(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__Adapter__getCount(env));
}

__attribute__((always_inline)) inline jclass J_get_class__AdapterView__OnItemSelectedListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.AdapterView__OnItemSelectedListener.class))
		handle_cache.AdapterView__OnItemSelectedListener.class = _REF((*env)->FindClass(env, "android/widget/AdapterView$OnItemSelectedListener"));

	return handle_cache.AdapterView__OnItemSelectedListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__AdapterView__OnItemSelectedListener__onItemSelected(JNIEnv *env)
{
	if (__unlikely__(handle_cache.AdapterView__OnItemSelectedListener.onItemSelected == 0))
		handle_cache.AdapterView__OnItemSelectedListener.onItemSelected = (*env)->GetMethodID(env, J_get_class__AdapterView__OnItemSelectedListener(env), "onItemSelected", "(Landroid/widget/AdapterView;Landroid/view/View;IJ)V");

	return handle_cache.AdapterView__OnItemSelectedListener.onItemSelected;
}

__attribute__((always_inline)) inline void J__AdapterView__OnItemSelectedListener__onItemSelected(JNIEnv *env, jobject this, jobject parent, jobject view, jint position, jlong id)
{
	(*env)->CallVoidMethod(env, this, J_get_method__AdapterView__OnItemSelectedListener__onItemSelected(env), parent, view, position, id);
}

__attribute__((always_inline)) inline jclass J_get_class__CompoundButton__OnCheckedChangeListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.CompoundButton__OnCheckedChangeListener.class))
		handle_cache.CompoundButton__OnCheckedChangeListener.class = _REF((*env)->FindClass(env, "android/widget/CompoundButton$OnCheckedChangeListener"));

	return handle_cache.CompoundButton__OnCheckedChangeListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__CompoundButton__OnCheckedChangeListener__onCheckedChanged(JNIEnv *env)
{
	if (__unlikely__(handle_cache.CompoundButton__OnCheckedChangeListener.onCheckedChanged == 0))
		handle_cache.CompoundButton__OnCheckedChangeListener.onCheckedChanged = (*env)->GetMethodID(env, J_get_class__CompoundButton__OnCheckedChangeListener(env), "onCheckedChanged", "(Landroid/widget/CompoundButton;Z)V");

	return handle_cache.CompoundButton__OnCheckedChangeListener.onCheckedChanged;
}

__attribute__((always_inline)) inline void J__CompoundButton__OnCheckedChangeListener__onCheckedChanged(JNIEnv *env, jobject this, jobject buttonView, jboolean isChecked)
{
	(*env)->CallVoidMethod(env, this, J_get_method__CompoundButton__OnCheckedChangeListener__onCheckedChanged(env), buttonView, isChecked);
}

__attribute__((always_inline)) inline jclass J_get_class__DatePicker(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.DatePicker.class))
		handle_cache.DatePicker.class = _REF((*env)->FindClass(env, "android/widget/DatePicker"));

	return handle_cache.DatePicker.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__DatePicker__onDateChange(JNIEnv *env)
{
	if (__unlikely__(handle_cache.DatePicker.onDateChange == 0))
		handle_cache.DatePicker.onDateChange = (*env)->GetMethodID(env, J_get_class__DatePicker(env), "onDateChange", "()V");

	return handle_cache.DatePicker.onDateChange;
}

__attribute__((always_inline)) inline void J__DatePicker__onDateChange(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__DatePicker__onDateChange(env));
}

__attribute__((always_inline)) inline jclass J_get_class__PopupMenu(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.PopupMenu.class))
		handle_cache.PopupMenu.class = _REF((*env)->FindClass(env, "android/widget/PopupMenu"));

	return handle_cache.PopupMenu.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__PopupMenu__menuItemClickCallback(JNIEnv *env)
{
	if (__unlikely__(handle_cache.PopupMenu.menuItemClickCallback == 0))
		handle_cache.PopupMenu.menuItemClickCallback = (*env)->GetMethodID(env, J_get_class__PopupMenu(env), "menuItemClickCallback", "(I)V");

	return handle_cache.PopupMenu.menuItemClickCallback;
}

__attribute__((always_inline)) inline void J__PopupMenu__menuItemClickCallback(JNIEnv *env, jobject this, jint id)
{
	(*env)->CallVoidMethod(env, this, J_get_method__PopupMenu__menuItemClickCallback(env), id);
}

__attribute__((always_inline)) inline jclass J_get_class__PopupWindow__OnDismissListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.PopupWindow__OnDismissListener.class))
		handle_cache.PopupWindow__OnDismissListener.class = _REF((*env)->FindClass(env, "android/widget/PopupWindow$OnDismissListener"));

	return handle_cache.PopupWindow__OnDismissListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__PopupWindow__OnDismissListener__onDismiss(JNIEnv *env)
{
	if (__unlikely__(handle_cache.PopupWindow__OnDismissListener.onDismiss == 0))
		handle_cache.PopupWindow__OnDismissListener.onDismiss = (*env)->GetMethodID(env, J_get_class__PopupWindow__OnDismissListener(env), "onDismiss", "()V");

	return handle_cache.PopupWindow__OnDismissListener.onDismiss;
}

__attribute__((always_inline)) inline void J__PopupWindow__OnDismissListener__onDismiss(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__PopupWindow__OnDismissListener__onDismiss(env));
}

__attribute__((always_inline)) inline jclass J_get_class__SeekBar__OnSeekBarChangeListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.SeekBar__OnSeekBarChangeListener.class))
		handle_cache.SeekBar__OnSeekBarChangeListener.class = _REF((*env)->FindClass(env, "android/widget/SeekBar$OnSeekBarChangeListener"));

	return handle_cache.SeekBar__OnSeekBarChangeListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__SeekBar__OnSeekBarChangeListener__onProgressChanged(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SeekBar__OnSeekBarChangeListener.onProgressChanged == 0))
		handle_cache.SeekBar__OnSeekBarChangeListener.onProgressChanged = (*env)->GetMethodID(env, J_get_class__SeekBar__OnSeekBarChangeListener(env), "onProgressChanged", "(Landroid/widget/SeekBar;IZ)V");

	return handle_cache.SeekBar__OnSeekBarChangeListener.onProgressChanged;
}

__attribute__((always_inline)) inline void J__SeekBar__OnSeekBarChangeListener__onProgressChanged(JNIEnv *env, jobject this, jobject seekBar, jint progress, jboolean fromUser)
{
	(*env)->CallVoidMethod(env, this, J_get_method__SeekBar__OnSeekBarChangeListener__onProgressChanged(env), seekBar, progress, fromUser);
}

__attribute__((always_inline)) inline jmethodID J_get_method__SeekBar__OnSeekBarChangeListener__onStartTrackingTouch(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SeekBar__OnSeekBarChangeListener.onStartTrackingTouch == 0))
		handle_cache.SeekBar__OnSeekBarChangeListener.onStartTrackingTouch = (*env)->GetMethodID(env, J_get_class__SeekBar__OnSeekBarChangeListener(env), "onStartTrackingTouch", "(Landroid/widget/SeekBar;)V");

	return handle_cache.SeekBar__OnSeekBarChangeListener.onStartTrackingTouch;
}

__attribute__((always_inline)) inline void J__SeekBar__OnSeekBarChangeListener__onStartTrackingTouch(JNIEnv *env, jobject this, jobject seekBar)
{
	(*env)->CallVoidMethod(env, this, J_get_method__SeekBar__OnSeekBarChangeListener__onStartTrackingTouch(env), seekBar);
}

__attribute__((always_inline)) inline jmethodID J_get_method__SeekBar__OnSeekBarChangeListener__onStopTrackingTouch(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SeekBar__OnSeekBarChangeListener.onStopTrackingTouch == 0))
		handle_cache.SeekBar__OnSeekBarChangeListener.onStopTrackingTouch = (*env)->GetMethodID(env, J_get_class__SeekBar__OnSeekBarChangeListener(env), "onStopTrackingTouch", "(Landroid/widget/SeekBar;)V");

	return handle_cache.SeekBar__OnSeekBarChangeListener.onStopTrackingTouch;
}

__attribute__((always_inline)) inline void J__SeekBar__OnSeekBarChangeListener__onStopTrackingTouch(JNIEnv *env, jobject this, jobject seekBar)
{
	(*env)->CallVoidMethod(env, this, J_get_method__SeekBar__OnSeekBarChangeListener__onStopTrackingTouch(env), seekBar);
}

__attribute__((always_inline)) inline jclass J_get_class__SpinnerAdapter(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.SpinnerAdapter.class))
		handle_cache.SpinnerAdapter.class = _REF((*env)->FindClass(env, "android/widget/SpinnerAdapter"));

	return handle_cache.SpinnerAdapter.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__SpinnerAdapter__getDropDownView(JNIEnv *env)
{
	if (__unlikely__(handle_cache.SpinnerAdapter.getDropDownView == 0))
		handle_cache.SpinnerAdapter.getDropDownView = (*env)->GetMethodID(env, J_get_class__SpinnerAdapter(env), "getDropDownView", "(ILandroid/view/View;Landroid/view/ViewGroup;)Landroid/view/View;");

	return handle_cache.SpinnerAdapter.getDropDownView;
}

__attribute__((always_inline)) inline jobject J__SpinnerAdapter__getDropDownView(JNIEnv *env, jobject this, jint position, jobject convertView, jobject parent)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__SpinnerAdapter__getDropDownView(env), position, convertView, parent);
}

__attribute__((always_inline)) inline jclass J_get_class__TextView__OnEditorActionListener(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.TextView__OnEditorActionListener.class))
		handle_cache.TextView__OnEditorActionListener.class = _REF((*env)->FindClass(env, "android/widget/TextView$OnEditorActionListener"));

	return handle_cache.TextView__OnEditorActionListener.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__TextView__OnEditorActionListener__onEditorAction(JNIEnv *env)
{
	if (__unlikely__(handle_cache.TextView__OnEditorActionListener.onEditorAction == 0))
		handle_cache.TextView__OnEditorActionListener.onEditorAction = (*env)->GetMethodID(env, J_get_class__TextView__OnEditorActionListener(env), "onEditorAction", "(Landroid/widget/TextView;ILandroid/view/KeyEvent;)Z");

	return handle_cache.TextView__OnEditorActionListener.onEditorAction;
}

__attribute__((always_inline)) inline jboolean J__TextView__OnEditorActionListener__onEditorAction(JNIEnv *env, jobject this, jobject v, jint actionId, jobject event)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__TextView__OnEditorActionListener__onEditorAction(env), v, actionId, event);
}

__attribute__((always_inline)) inline jclass J_get_class__TimePicker(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.TimePicker.class))
		handle_cache.TimePicker.class = _REF((*env)->FindClass(env, "android/widget/TimePicker"));

	return handle_cache.TimePicker.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__TimePicker__onTimeChange(JNIEnv *env)
{
	if (__unlikely__(handle_cache.TimePicker.onTimeChange == 0))
		handle_cache.TimePicker.onTimeChange = (*env)->GetMethodID(env, J_get_class__TimePicker(env), "onTimeChange", "()V");

	return handle_cache.TimePicker.onTimeChange;
}

__attribute__((always_inline)) inline void J__TimePicker__onTimeChange(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__TimePicker__onTimeChange(env));
}

__attribute__((always_inline)) inline jclass J_get_class__InputStream(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.InputStream.class))
		handle_cache.InputStream.class = _REF((*env)->FindClass(env, "java/io/InputStream"));

	return handle_cache.InputStream.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__InputStream__read(JNIEnv *env)
{
	if (__unlikely__(handle_cache.InputStream.read == 0))
		handle_cache.InputStream.read = (*env)->GetMethodID(env, J_get_class__InputStream(env), "read", "([BII)I");

	return handle_cache.InputStream.read;
}

__attribute__((always_inline)) inline jint J__InputStream__read(JNIEnv *env, jobject this, jbyteArray _arg0, jint _arg1, jint _arg2)
{
	return (*env)->CallIntMethod(env, this, J_get_method__InputStream__read(env), _arg0, _arg1, _arg2);
}

__attribute__((always_inline)) inline jclass J_get_class__CharSequence(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.CharSequence.class))
		handle_cache.CharSequence.class = _REF((*env)->FindClass(env, "java/lang/CharSequence"));

	return handle_cache.CharSequence.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__CharSequence__toString(JNIEnv *env)
{
	if (__unlikely__(handle_cache.CharSequence.toString == 0))
		handle_cache.CharSequence.toString = (*env)->GetMethodID(env, J_get_class__CharSequence(env), "toString", "()Ljava/lang/String;");

	return handle_cache.CharSequence.toString;
}

__attribute__((always_inline)) inline jstring J__CharSequence__toString(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__CharSequence__toString(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Class(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Class.class))
		handle_cache.Class.class = _REF((*env)->FindClass(env, "java/lang/Class"));

	return handle_cache.Class.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Class__getClassLoader(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Class.getClassLoader == 0))
		handle_cache.Class.getClassLoader = (*env)->GetMethodID(env, J_get_class__Class(env), "getClassLoader", "()Ljava/lang/ClassLoader;");

	return handle_cache.Class.getClassLoader;
}

__attribute__((always_inline)) inline jobject J__Class__getClassLoader(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Class__getClassLoader(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Class__getName(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Class.getName == 0))
		handle_cache.Class.getName = (*env)->GetMethodID(env, J_get_class__Class(env), "getName", "()Ljava/lang/String;");

	return handle_cache.Class.getName;
}

__attribute__((always_inline)) inline jstring J__Class__getName(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Class__getName(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Runtime(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Runtime.class))
		handle_cache.Runtime.class = _REF((*env)->FindClass(env, "java/lang/Runtime"));

	return handle_cache.Runtime.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Runtime__getRuntime(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Runtime.getRuntime == 0))
		handle_cache.Runtime.getRuntime = (*env)->GetStaticMethodID(env, J_get_class__Runtime(env), "getRuntime", "()Ljava/lang/Runtime;");

	return handle_cache.Runtime.getRuntime;
}

__attribute__((always_inline)) inline jobject J__Runtime__getRuntime(JNIEnv *env)
{
	jclass class = J_get_class__Runtime(env);
	return (*env)->CallStaticObjectMethod(env, class, J_get_method__Runtime__getRuntime(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Runtime__loadLibrary(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Runtime.loadLibrary == 0))
		handle_cache.Runtime.loadLibrary = (*env)->GetMethodID(env, J_get_class__Runtime(env), "loadLibrary", "(Ljava/lang/String;Ljava/lang/ClassLoader;)V");

	return handle_cache.Runtime.loadLibrary;
}

__attribute__((always_inline)) inline void J__Runtime__loadLibrary(JNIEnv *env, jobject this, jstring _arg0, jobject _arg1)
{
	(*env)->CallVoidMethod(env, this, J_get_method__Runtime__loadLibrary(env), _arg0, _arg1);
}

__attribute__((always_inline)) inline jclass J_get_class__System(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.System.class))
		handle_cache.System.class = _REF((*env)->FindClass(env, "java/lang/System"));

	return handle_cache.System.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__System__exit(JNIEnv *env)
{
	if (__unlikely__(handle_cache.System.exit == 0))
		handle_cache.System.exit = (*env)->GetStaticMethodID(env, J_get_class__System(env), "exit", "(I)V");

	return handle_cache.System.exit;
}

__attribute__((always_inline)) inline void J__System__exit(JNIEnv *env, jint _arg0)
{
	jclass class = J_get_class__System(env);
	return (*env)->CallStaticVoidMethod(env, class, J_get_method__System__exit(env), _arg0);
}

__attribute__((always_inline)) inline jclass J_get_class__Buffer(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Buffer.class))
		handle_cache.Buffer.class = _REF((*env)->FindClass(env, "java/nio/Buffer"));

	return handle_cache.Buffer.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Buffer__array(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Buffer.array == 0))
		handle_cache.Buffer.array = (*env)->GetMethodID(env, J_get_class__Buffer(env), "array", "()Ljava/lang/Object;");

	return handle_cache.Buffer.array;
}

__attribute__((always_inline)) inline jobject J__Buffer__array(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Buffer__array(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__Buffer__arrayOffset(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Buffer.arrayOffset == 0))
		handle_cache.Buffer.arrayOffset = (*env)->GetMethodID(env, J_get_class__Buffer(env), "arrayOffset", "()I");

	return handle_cache.Buffer.arrayOffset;
}

__attribute__((always_inline)) inline jint J__Buffer__arrayOffset(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__Buffer__arrayOffset(env));
}

__attribute__((always_inline)) inline jclass J_get_class__ArrayList(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.ArrayList.class))
		handle_cache.ArrayList.class = _REF((*env)->FindClass(env, "java/util/ArrayList"));

	return handle_cache.ArrayList.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__ArrayList__add(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ArrayList.add == 0))
		handle_cache.ArrayList.add = (*env)->GetMethodID(env, J_get_class__ArrayList(env), "add", "(Ljava/lang/Object;)Z");

	return handle_cache.ArrayList.add;
}

__attribute__((always_inline)) inline jboolean J__ArrayList__add(JNIEnv *env, jobject this, jobject _arg0)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__ArrayList__add(env), _arg0);
}

__attribute__((always_inline)) inline jmethodID J_get_method__ArrayList__clear(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ArrayList.clear == 0))
		handle_cache.ArrayList.clear = (*env)->GetMethodID(env, J_get_class__ArrayList(env), "clear", "()V");

	return handle_cache.ArrayList.clear;
}

__attribute__((always_inline)) inline void J__ArrayList__clear(JNIEnv *env, jobject this)
{
	(*env)->CallVoidMethod(env, this, J_get_method__ArrayList__clear(env));
}

__attribute__((always_inline)) inline jmethodID J_get_method__ArrayList__get(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ArrayList.get == 0))
		handle_cache.ArrayList.get = (*env)->GetMethodID(env, J_get_class__ArrayList(env), "get", "(I)Ljava/lang/Object;");

	return handle_cache.ArrayList.get;
}

__attribute__((always_inline)) inline jobject J__ArrayList__get(JNIEnv *env, jobject this, jint _arg0)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__ArrayList__get(env), _arg0);
}

__attribute__((always_inline)) inline jmethodID J_get_method__ArrayList__remove(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ArrayList.remove == 0))
		handle_cache.ArrayList.remove = (*env)->GetMethodID(env, J_get_class__ArrayList(env), "remove", "(Ljava/lang/Object;)Z");

	return handle_cache.ArrayList.remove;
}

__attribute__((always_inline)) inline jboolean J__ArrayList__remove(JNIEnv *env, jobject this, jobject _arg0)
{
	return (*env)->CallBooleanMethod(env, this, J_get_method__ArrayList__remove(env), _arg0);
}

__attribute__((always_inline)) inline jmethodID J_get_method__ArrayList__size(JNIEnv *env)
{
	if (__unlikely__(handle_cache.ArrayList.size == 0))
		handle_cache.ArrayList.size = (*env)->GetMethodID(env, J_get_class__ArrayList(env), "size", "()I");

	return handle_cache.ArrayList.size;
}

__attribute__((always_inline)) inline jint J__ArrayList__size(JNIEnv *env, jobject this)
{
	return (*env)->CallIntMethod(env, this, J_get_method__ArrayList__size(env));
}

__attribute__((always_inline)) inline jclass J_get_class__Set(JNIEnv *env)
{
	if (__unlikely__(!handle_cache.Set.class))
		handle_cache.Set.class = _REF((*env)->FindClass(env, "java/util/Set"));

	return handle_cache.Set.class;
}

__attribute__((always_inline)) inline jmethodID J_get_method__Set__toArray(JNIEnv *env)
{
	if (__unlikely__(handle_cache.Set.toArray == 0))
		handle_cache.Set.toArray = (*env)->GetMethodID(env, J_get_class__Set(env), "toArray", "()[Ljava/lang/Object;");

	return handle_cache.Set.toArray;
}

__attribute__((always_inline)) inline jobjectArray J__Set__toArray(JNIEnv *env, jobject this)
{
	return (*env)->CallObjectMethod(env, this, J_get_method__Set__toArray(env));
}
#endif
