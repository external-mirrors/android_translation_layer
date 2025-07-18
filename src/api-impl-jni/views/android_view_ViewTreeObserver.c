#include <gtk/gtk.h>

#include "../defines.h"
#include "../util.h"
#include "../generated_headers/android_view_ViewTreeObserver.h"

static void on_global_layout_callback(GdkFrameClock *clock, jobject view_tree_observer)
{
	JNIEnv *env = get_jni_env();
	(*env)->CallVoidMethod(env, view_tree_observer, handle_cache.view_tree_observer.dispatchOnGlobalLayout);
	if((*env)->ExceptionCheck(env)) {
		(*env)->ExceptionDescribe(env);
		(*env)->ExceptionClear(env);
	}
}

JNIEXPORT void JNICALL Java_android_view_ViewTreeObserver_native_1set_1have_1global_1layout_1listeners(JNIEnv *env, jobject this, jboolean have_listeners)
{
	GtkWidget *window =_PTR(_GET_LONG_FIELD(this, "window"));

	if(!window) {
		/* FIXME: calling this on unrooted widgets may be valid */
		fprintf(stderr, "in Java_android_view_ViewTreeObserver_native_1set_1have_1global_1layout_1listeners: no window\n");
		return;
	}

	GdkFrameClock *clock = gtk_widget_get_frame_clock(window);

	if(have_listeners) {
		/* this adds our callback before the existing handler, which means we effectively execute before the paint phase (after layout) */
		gulong signal_handle = g_signal_connect(G_OBJECT(clock), "paint", G_CALLBACK(on_global_layout_callback), _REF(this)); // FIXME: cleanup callback for _UNREF
		_SET_LONG_FIELD(this, "onGlobalLayout_signal_handle", signal_handle);
	} else {
		gulong signal_handle = _GET_LONG_FIELD(this, "onGlobalLayout_signal_handle");
		if (signal_handle)
			g_signal_handler_disconnect(G_OBJECT(clock), signal_handle);
	}
}
