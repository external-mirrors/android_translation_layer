#include <gtk/gtk.h>

#include "../defines.h"
#include "../util.h"

#include "WrapperWidget.h"

#include "../generated_headers/android_widget_PopupWindow.h"

JNIEXPORT jlong JNICALL Java_android_widget_PopupWindow_native_1constructor(JNIEnv *env, jobject this)
{
	GtkWidget *popover = gtk_popover_new();
	gtk_widget_set_name(popover, "PopupWindow");
	return _INTPTR(popover);
}

JNIEXPORT void JNICALL Java_android_widget_PopupWindow_native_1setContentView(JNIEnv *env, jobject this, jlong popover_ptr, jlong content_ptr)
{
	WrapperWidget *content = WRAPPER_WIDGET(gtk_widget_get_parent(GTK_WIDGET(_PTR(content_ptr))));
	gtk_popover_set_child(GTK_POPOVER(_PTR(popover_ptr)), GTK_WIDGET(content));
}

JNIEXPORT void JNICALL Java_android_widget_PopupWindow_native_1showAsDropDown(JNIEnv *env, jobject this, jlong popover_ptr, jlong anchor_ptr, jint x, jint y, jint gravity)
{
	GtkPopover *popover = GTK_POPOVER(_PTR(popover_ptr));
	WrapperWidget *anchor = WRAPPER_WIDGET(gtk_widget_get_parent(GTK_WIDGET(_PTR(anchor_ptr))));

	gtk_widget_insert_before(GTK_WIDGET(popover), GTK_WIDGET(anchor), NULL);
	gtk_popover_present(GTK_POPOVER(popover));
	gtk_popover_popup(popover);
}

JNIEXPORT void JNICALL Java_android_widget_PopupWindow_setWidth(JNIEnv *env, jobject this, jint width)
{
	int height;
	GtkWidget *popover = GTK_WIDGET(_PTR(_GET_LONG_FIELD(this, "popover")));
	gtk_widget_get_size_request(popover, NULL, &height);
	gtk_widget_set_size_request(popover, width, height);
}

JNIEXPORT void JNICALL Java_android_widget_PopupWindow_setHeight(JNIEnv *env, jobject this, jint height)
{
	int width;
	GtkWidget *popover = GTK_WIDGET(_PTR(_GET_LONG_FIELD(this, "popover")));
	gtk_widget_get_size_request(popover, &width, NULL);
	gtk_widget_set_size_request(popover, width, height);
}

static void on_closed_cb(GtkPopover *popover, jobject listener)
{
	JNIEnv *env = get_jni_env();
	jmethodID onDismiss = _METHOD(_CLASS(listener), "onDismiss", "()V");
	(*env)->CallVoidMethod(env, listener, onDismiss);
}

JNIEXPORT void JNICALL Java_android_widget_PopupWindow_setOnDismissListener(JNIEnv *env, jobject this, jobject listener)
{
	GtkWidget *popover = GTK_WIDGET(_PTR(_GET_LONG_FIELD(this, "popover")));
	g_signal_connect(popover, "closed", G_CALLBACK(on_closed_cb), _REF(listener));
}

JNIEXPORT jboolean JNICALL Java_android_widget_PopupWindow_native_1isShowing(JNIEnv *env, jobject this, jlong popover_ptr)
{
	return gtk_widget_get_visible(GTK_WIDGET(_PTR(popover_ptr)));
}

JNIEXPORT void JNICALL Java_android_widget_PopupWindow_native_1dismiss(JNIEnv *env, jobject this, jlong popover_ptr)
{
	gtk_popover_popdown(GTK_POPOVER(_PTR(popover_ptr)));
}
