#include <gtk/gtk.h>

#include "defines.h"
#include "util.h"

#include "generated_headers/android_view_Window.h"

JNIEXPORT void JNICALL Java_android_view_Window_set_1widget_1as_1root(JNIEnv *env, jobject this, jlong window, jlong widget)
{
	GtkWindow *gtk_window = GTK_WINDOW(_PTR(window));
	GtkWidget *gtk_widget = gtk_widget_get_parent(GTK_WIDGET(_PTR(widget)));
	if (gtk_widget != gtk_window_get_child(gtk_window)) {
		gtk_window_set_child(gtk_window, gtk_widget);
	}
}

JNIEXPORT void JNICALL Java_android_view_Window_set_1title(JNIEnv *env, jobject this, jlong window, jstring title_jstr)
{
	GtkWindow *gtk_window = GTK_WINDOW(_PTR(window));
	const char *title = (*env)->GetStringUTFChars(env, title_jstr, NULL);
	gtk_window_set_title(gtk_window, title);
	(*env)->ReleaseStringUTFChars(env, title_jstr, title);
}

// FIXME put this in a header file
struct input_queue {
	int fd;
	GtkEventController *controller;
};

JNIEXPORT void JNICALL Java_android_view_Window_take_1input_1queue(JNIEnv *env, jobject this, jlong native_window, jobject callback, jobject queue)
{
	GtkWidget *window = _PTR(native_window);
	printf("in Java_android_view_Window_take_1input_1queue\n");

	GtkEventController *controller = GTK_EVENT_CONTROLLER(gtk_event_controller_legacy_new());
	gtk_widget_add_controller(window, controller);

	struct input_queue *input_queue = malloc(sizeof(struct input_queue));
	input_queue->fd = -1;
	input_queue->controller = controller;

	_SET_LONG_FIELD(queue, "native_ptr", _INTPTR(input_queue));

	// we need to keep these for later, so they can be called after OnCreate finishes
	g_object_set_data(G_OBJECT(window), "input_queue_callback", (gpointer)_REF(callback));
	g_object_set_data(G_OBJECT(window), "input_queue", (gpointer)_REF(queue));
}

JNIEXPORT void JNICALL Java_android_view_Window_set_1layout(JNIEnv *env, jobject this, jlong window, jint width, jint height)
{
	GtkWindow *gtk_window = GTK_WINDOW(_PTR(window));
	if (width > 0 && height > 0)
		gtk_window_set_default_size(gtk_window, width, height);
}

JNIEXPORT void JNICALL Java_android_view_Window_set_1jobject(JNIEnv *env, jclass this, jlong window, jobject window_jobj)
{
	g_object_set_data(G_OBJECT(window), "jobject", _WEAK_REF(window_jobj));
}

JNIEXPORT void JNICALL Java_android_view_Window_remove_1gtk_1background(JNIEnv *env, jobject this, jlong window)
{
	gtk_widget_add_css_class(GTK_WIDGET(_PTR(window)), "ATL-no-background");
}
