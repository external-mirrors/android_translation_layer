#include <gtk/gtk.h>

#include "../defines.h"
#include "../util.h"

#include "WrapperWidget.h"

#include "../generated_headers/android_widget_Button.h"

JNIEXPORT jlong JNICALL Java_android_widget_Button_native_1constructor(JNIEnv *env, jobject this, jobject context, jobject attrs)
{
	const char *text = attribute_set_get_string(env, attrs, "text", NULL);

	GtkWidget *wrapper = g_object_ref(wrapper_widget_new());
	GtkWidget *label = gtk_button_new_with_label(text);
	wrapper_widget_set_child(WRAPPER_WIDGET(wrapper), label);
	wrapper_widget_consume_touch_events(WRAPPER_WIDGET(wrapper));  // Android button consumes touch events
	wrapper_widget_set_jobject(WRAPPER_WIDGET(wrapper), env, this);

	return _INTPTR(label);
}

JNIEXPORT void JNICALL Java_android_widget_Button_native_1setText(JNIEnv *env, jobject this, jlong widget_ptr, jobject text)
{
	GtkButton *button = GTK_BUTTON(_PTR(widget_ptr));

	const char *nativeText = ((*env)->GetStringUTFChars(env, text, NULL));
	gtk_button_set_label(button, nativeText);
	((*env)->ReleaseStringUTFChars(env, text, nativeText));
}

static void clicked_cb(GtkWidget *button, gpointer user_data) {
	JNIEnv *env = get_jni_env();
	WrapperWidget *wrapper = WRAPPER_WIDGET(gtk_widget_get_parent(button));

	(*env)->CallBooleanMethod(env, wrapper->jobj, handle_cache.view.performClick);

	if((*env)->ExceptionCheck(env))
		(*env)->ExceptionDescribe(env);
}

JNIEXPORT void JNICALL Java_android_widget_Button_nativeSetOnClickListener(JNIEnv *env, jobject this, jlong widget_ptr)
{
	GtkWidget *button = GTK_WIDGET(_PTR(widget_ptr));
	g_signal_handlers_disconnect_matched(button, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, clicked_cb, NULL);

	g_signal_connect(button, "clicked", G_CALLBACK(clicked_cb), NULL);
}

JNIEXPORT jobject JNICALL Java_android_widget_Button_getText(JNIEnv *env, jobject this)
{
	GtkButton *button = GTK_BUTTON(_PTR(_GET_LONG_FIELD(this, "widget")));
	return (*env)->NewStringUTF(env, gtk_button_get_label(button));
}
