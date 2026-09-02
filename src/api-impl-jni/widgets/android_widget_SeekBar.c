#include <gtk/gtk.h>
#include <stdio.h>

#include "../defines.h"
#include "../util.h"

#include "WrapperWidget.h"

#include "../generated_headers/android_widget_SeekBar.h"
#include "jni.h"

JNIEXPORT jlong JNICALL Java_android_widget_SeekBar_native_1constructor(JNIEnv *env, jobject this, jobject context, jobject attrs)
{
	GtkWidget *wrapper = g_object_ref(wrapper_widget_new());
	GtkWidget *scale = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, NULL);
	gtk_range_set_range(GTK_RANGE(scale), 0, 100);
	wrapper_widget_set_child(WRAPPER_WIDGET(wrapper), scale);
	wrapper_widget_set_jobject(WRAPPER_WIDGET(wrapper), env, this);
	gtk_widget_set_name(scale, "SeekBar");
	return _INTPTR(scale);
}

JNIEXPORT void JNICALL Java_android_widget_SeekBar_native_1setMax(JNIEnv *env, jobject this, jlong widget_ptr, jint max)
{
	GtkRange *range = GTK_RANGE(_PTR(widget_ptr));
	gtk_range_set_range(range, 0, max);
}

JNIEXPORT void JNICALL Java_android_widget_SeekBar_native_1setProgress(JNIEnv *env, jobject this, jlong widget_ptr, jfloat progress)
{
	GtkRange *range = GTK_RANGE(_PTR(widget_ptr));
	gtk_range_set_value(range, progress);
}

static void on_change_value(GtkRange *self, GtkScrollType *scroll, gdouble value, jobject listener)
{
	JNIEnv *env = get_jni_env();
	WrapperWidget *wrapper = WRAPPER_WIDGET(gtk_widget_get_parent(GTK_WIDGET(self)));
	J__SeekBar__OnSeekBarChangeListener__onStartTrackingTouch(env, listener, wrapper->jobj);
	J__SeekBar__OnSeekBarChangeListener__onProgressChanged(env, listener, wrapper->jobj, (int)value, TRUE);
	J__SeekBar__OnSeekBarChangeListener__onStopTrackingTouch(env, listener, wrapper->jobj);
}

JNIEXPORT void JNICALL Java_android_widget_SeekBar_setOnSeekBarChangeListener(JNIEnv *env, jobject this, jobject listener)
{
	GtkRange *range = GTK_RANGE(_PTR(_GET_LONG_FIELD(this, "widget")));
	g_signal_handlers_disconnect_matched(range, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, on_change_value, NULL);
	if (listener) {
		g_signal_connect(range, "change_value", G_CALLBACK(on_change_value), _REF(listener));
	}
}

JNIEXPORT jint JNICALL Java_android_widget_SeekBar_native_1getProgress(JNIEnv *env, jobject this, jlong widget_ptr)
{
	GtkRange *range = GTK_RANGE(_PTR(widget_ptr));
	return gtk_range_get_value(range);
}
