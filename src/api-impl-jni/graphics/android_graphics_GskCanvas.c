#include <gtk/gtk.h>
#include <graphene.h>
#include <pango/pango.h>

#include "../defines.h"
#include "AndroidPaint.h"

#include "../generated_headers/android_graphics_GskCanvas.h"

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawBitmap(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jlong texture_ptr, jint x, jint y, jint width, jint height, jlong paint_ptr)
{
	GdkSnapshot *snapshot = (GdkSnapshot *)_PTR(snapshot_ptr);
	GdkTexture *texture = GDK_TEXTURE(_PTR(texture_ptr));
	struct AndroidPaint *paint = _PTR(paint_ptr);
	if (paint->use_color_filter) {
		gtk_snapshot_push_color_matrix(snapshot, &paint->color_matrix, &paint->color_offset);
	}
	gtk_snapshot_append_texture(snapshot, texture, &GRAPHENE_RECT_INIT(x, y, width, height));
	if (paint->use_color_filter)
		gtk_snapshot_pop(snapshot);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawRect(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat left, jfloat top, jfloat right, jfloat bottom, jlong paint_ptr)
{
	GdkSnapshot *snapshot = (GdkSnapshot *)_PTR(snapshot_ptr);
	struct AndroidPaint *paint = _PTR(paint_ptr);
	graphene_rect_t bounds = GRAPHENE_RECT_INIT(left, top, right - left, bottom - top);
	gtk_snapshot_append_color(snapshot, &paint->color, &bounds);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawPath(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jlong path_ptr, jlong paint_ptr)
{
	GtkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	GskPath *path = _PTR(path_ptr);
	struct AndroidPaint *paint = _PTR(paint_ptr);
	if (paint->is_stroke) {
		gtk_snapshot_append_stroke(snapshot, path, paint->gsk_stroke, &paint->color);
	}
	if (paint->is_fill) {
		gtk_snapshot_append_fill(snapshot, path, GSK_FILL_RULE_WINDING, &paint->color);
	}
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1translate(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat dx, jfloat dy)
{
	GtkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	gtk_snapshot_translate(snapshot, &GRAPHENE_POINT_INIT(dx, dy));
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1rotate(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat angle)
{
	GtkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	gtk_snapshot_rotate(snapshot, angle);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1save(JNIEnv *env, jclass this_class, jlong snapshot_ptr)
{
	GtkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	gtk_snapshot_save(snapshot);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1restore(JNIEnv *env, jclass this_class, jlong snapshot_ptr)
{
	GtkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	gtk_snapshot_restore(snapshot);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawLine(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat x0, jfloat y0, jfloat x1, jfloat y1, jlong paint_ptr)
{
	if (isnan(x0) || isnan(y0) || isnan(x1) || isnan(y1)) {
		return;
	}
	GdkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	struct AndroidPaint *paint = _PTR(paint_ptr);
	gtk_snapshot_save(snapshot);
	gtk_snapshot_translate(snapshot, &GRAPHENE_POINT_INIT(x0, y0));
	float rotation = atan2(y1 - y0, x1 - x0);
	gtk_snapshot_rotate(snapshot, rotation * 180 / M_PI);
	float length = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	float stroke_width = gsk_stroke_get_line_width(paint->gsk_stroke);
	gtk_snapshot_append_color(snapshot, &paint->color, &GRAPHENE_RECT_INIT(0, -stroke_width / 2, length, stroke_width));
	gtk_snapshot_restore(snapshot);
}

extern GtkWidget *window;

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawText(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jstring text, jfloat x, jfloat y, jlong paint_ptr)
{
	GdkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	struct AndroidPaint *paint = _PTR(paint_ptr);
	PangoLayout *layout = pango_layout_new(gtk_widget_get_pango_context(window));
	pango_layout_set_font_description(layout, paint->font);
	const char *str = (*env)->GetStringUTFChars(env, text, NULL);
	pango_layout_set_text(layout, str, -1);
	(*env)->ReleaseStringUTFChars(env, text, str);
	gtk_snapshot_translate(snapshot, &GRAPHENE_POINT_INIT(x, y));
	gtk_snapshot_append_layout(snapshot, layout, &paint->color);
	gtk_snapshot_translate(snapshot, &GRAPHENE_POINT_INIT(-x, -y));
	g_object_unref(layout);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawRoundRect(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat left, jfloat top, jfloat right, jfloat bottom, jfloat rx, jfloat ry, jlong paint_ptr)
{
	GdkSnapshot *snapshot = (GdkSnapshot *)_PTR(snapshot_ptr);
	struct AndroidPaint *paint = _PTR(paint_ptr);
	GdkRGBA gdk_color[4];
	for (int i = 0; i < 4; i++) {
		gdk_color[i].red = paint->color.red;
		gdk_color[i].green = paint->color.green;
		gdk_color[i].blue = paint->color.blue;
		gdk_color[i].alpha = paint->color.alpha;
	}
	GskRoundedRect round_rect = {
		.bounds = GRAPHENE_RECT_INIT(left, top, right - left, bottom - top),
		.corner = {{rx, ry}, {rx, ry}, {rx, ry}, {rx, ry}},
	};
	float width = gsk_stroke_get_line_width(paint->gsk_stroke);
	const float widths[4] = {width, width, width, width};
	if (paint->is_fill) {
		gtk_snapshot_push_rounded_clip(snapshot, &round_rect);
		gtk_snapshot_append_color(snapshot, gdk_color, &round_rect.bounds);
		gtk_snapshot_pop(snapshot);
	}
	if (paint->is_stroke) {
		gtk_snapshot_append_border(snapshot, &round_rect, widths, gdk_color);
	}
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1scale(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat x, jfloat y)
{
	GdkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	gtk_snapshot_scale(snapshot, x, y);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1concat(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jlong matrix_ptr)
{
	GdkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	graphene_matrix_t *matrix = (graphene_matrix_t *)_PTR(matrix_ptr);
	gtk_snapshot_transform_matrix(snapshot, matrix);
}
