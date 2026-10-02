#include <gtk/gtk.h>

#include "../defines.h"
#include "../util.h"

#include "WrapperWidget.h"

#include "../generated_headers/android_widget_ScrollView.h"

JNIEXPORT jlong JNICALL Java_android_widget_ScrollView_native_1constructor(JNIEnv *env, jobject this, jobject context, jobject attrs)
{
	GtkWidget *wrapper = g_object_ref(wrapper_widget_new());
	GtkWidget *scrolled_window = gtk_scrolled_window_new();
	GtkWidget *viewport = gtk_viewport_new(NULL, NULL);
	gtk_scrollable_set_vscroll_policy(GTK_SCROLLABLE(viewport), GTK_SCROLL_NATURAL);
	wrapper_widget_set_child(WRAPPER_WIDGET(wrapper), scrolled_window);
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), viewport);
	gtk_widget_set_name(scrolled_window, "ScrollView");
	return _INTPTR(scrolled_window);
}

JNIEXPORT void JNICALL Java_android_widget_ScrollView_native_1addView(JNIEnv *env, jobject this, jlong widget_ptr, jlong child_ptr, jint index, jobject params)
{
	GtkScrolledWindow *widget = _PTR(widget_ptr);
	GtkWidget *viewport = gtk_scrolled_window_get_child(widget);
	GtkWidget *child = gtk_widget_get_parent(_PTR(child_ptr));

	gtk_viewport_set_child(GTK_VIEWPORT(viewport), child);
}

JNIEXPORT void JNICALL Java_android_widget_ScrollView_native_1removeView(JNIEnv *env, jobject this, jlong widget_ptr, jlong child_ptr)
{
	GtkScrolledWindow *widget = _PTR(widget_ptr);
	GtkWidget *viewport = gtk_scrolled_window_get_child(widget);

	gtk_viewport_set_child(GTK_VIEWPORT(viewport), NULL);
}
