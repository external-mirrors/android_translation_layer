#include <gtk/gtk.h>
#include <pango/pango.h>

#include "../defines.h"
#include "../graphics/AndroidPaint.h"
#include "../generated_headers/android_text_Layout.h"

extern GtkWidget *window;

JNIEXPORT jlong JNICALL Java_android_text_Layout_native_1constructor(JNIEnv *env, jobject object, jstring text, jlong paint, jint width)
{
	struct AndroidPaint *android_paint = _PTR(paint);
	PangoLayout *layout = pango_layout_new(gtk_widget_get_pango_context(window));
	pango_layout_set_font_description(layout, android_paint->font);
	const char *str = (*env)->GetStringUTFChars(env, text, NULL);
	pango_layout_set_text(layout, str, -1);
	(*env)->ReleaseStringUTFChars(env, text, str);
	pango_layout_set_width(layout, width * PANGO_SCALE);
	return _INTPTR(layout);
}

JNIEXPORT void JNICALL Java_android_text_Layout_native_1set_1width(JNIEnv *env, jobject object, jlong layout, jint width)
{
	PangoLayout *pango_layout = _PTR(layout);
	pango_layout_set_width(pango_layout, width * PANGO_SCALE);
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1width(JNIEnv *env, jobject object, jlong layout)
{
	PangoLayout *pango_layout = _PTR(layout);
	return pango_layout_get_width(pango_layout) / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1height(JNIEnv *env, jobject object, jlong layout)
{
	PangoLayout *pango_layout = _PTR(layout);
	PangoRectangle ink_rect;
	PangoRectangle logical_rect;
	pango_layout_get_extents(pango_layout, &ink_rect, &logical_rect);
	return logical_rect.height / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1count(JNIEnv *env, jobject object, jlong layout)
{
	PangoLayout *pango_layout = _PTR(layout);
	return pango_layout_get_line_count(pango_layout);
}

static void get_line_extends(PangoLayout *pango_layout, int line, PangoRectangle *logical_rect) {
	PangoRectangle ink_rect;
	PangoLayoutIter *pango_iter = pango_layout_get_iter(pango_layout);
	while (line--)
		pango_layout_iter_next_line(pango_iter);
	pango_layout_iter_get_line_extents(pango_iter, &ink_rect, logical_rect);
	pango_layout_iter_free(pango_iter);
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1top(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoRectangle logical_rect;
	get_line_extends(PANGO_LAYOUT(_PTR(layout)), line, &logical_rect);
	return (logical_rect.y) / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1bottom(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoRectangle logical_rect;
	get_line_extends(PANGO_LAYOUT(_PTR(layout)), line, &logical_rect);
	return (logical_rect.y + logical_rect.height) / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1left(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoRectangle logical_rect;
	get_line_extends(PANGO_LAYOUT(_PTR(layout)), line, &logical_rect);
	return logical_rect.x / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1right(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoRectangle logical_rect;
	get_line_extends(PANGO_LAYOUT(_PTR(layout)), line, &logical_rect);
	return (logical_rect.x + logical_rect.width) / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1width(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoRectangle logical_rect;
	get_line_extends(PANGO_LAYOUT(_PTR(layout)), line, &logical_rect);
	return logical_rect.width / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1baseline(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoLayout *pango_layout = _PTR(layout);
	PangoLayoutIter *pango_iter = pango_layout_get_iter(pango_layout);
	while (line--)
		pango_layout_iter_next_line(pango_iter);

	return pango_layout_iter_get_baseline(pango_iter) / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1ascent(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoLayout *pango_layout = _PTR(layout);
	PangoLayoutLine *pango_line = pango_layout_get_line_readonly(pango_layout, line);
	PangoRectangle logical_rect, ink_rect;
	pango_layout_line_get_extents(pango_line, &logical_rect, &ink_rect);
	return -PANGO_ASCENT(ink_rect) / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1descent(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoLayout *pango_layout = _PTR(layout);
	PangoLayoutLine *pango_line = pango_layout_get_line_readonly(pango_layout, line);
	PangoRectangle logical_rect, ink_rect;
	pango_layout_line_get_extents(pango_line, &logical_rect, &ink_rect);
	return PANGO_DESCENT(ink_rect) / PANGO_SCALE;
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1line_1for_1vertical(JNIEnv *env, jobject object, jlong layout, jint y)
{
	PangoLayout *pango_layout = _PTR(layout);
	int index_, trailing;
	pango_layout_xy_to_index(pango_layout, 0, y * PANGO_SCALE, &index_, &trailing);
	int line, x_pos;
	pango_layout_index_to_line_x(pango_layout, index_, trailing, &line, &x_pos);
	return line;
}

JNIEXPORT void JNICALL Java_android_text_Layout_native_1set_1ellipsize(JNIEnv *env, jobject object, jlong layout, jint ellipsize_mode, jfloat ellipsize_width)
{
	PangoLayout *pango_layout = _PTR(layout);
	pango_layout_set_ellipsize(pango_layout, (PangoEllipsizeMode)ellipsize_mode);
	pango_layout_set_width(pango_layout, ellipsize_width * PANGO_SCALE);
}

JNIEXPORT jint JNICALL Java_android_text_Layout_native_1get_1ellipsis_1count(JNIEnv *env, jobject object, jlong layout, jint line)
{
	PangoLayout *pango_layout = _PTR(layout);
	return pango_layout_is_ellipsized(pango_layout);
}

JNIEXPORT void JNICALL Java_android_text_Layout_native_1draw(JNIEnv *env, jobject object, jlong layout, jlong snapshot_ptr, jlong paint_ptr)
{
	PangoLayout *pango_layout = PANGO_LAYOUT(_PTR(layout));
	GtkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	struct AndroidPaint *android_paint = _PTR(paint_ptr);

	gtk_snapshot_append_layout(snapshot, pango_layout, &android_paint->color);
}
