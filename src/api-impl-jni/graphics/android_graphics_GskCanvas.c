#include <gtk/gtk.h>
#include <graphene.h>
#include <pango/pango.h>

#include "../defines.h"

#include "../generated_headers/android_graphics_GskCanvas.h"

#define STYLE_FILL 0
#define STYLE_STROKE 1
#define STYLE_FILL_AND_STROKE 2

#define GDK_RGBA_INIT(color) ((GdkRGBA){ \
	.red = ((color >> 16) & 0xFF) / 255.f, \
	.green = ((color >> 8) & 0xFF) / 255.f, \
	.blue = ((color >> 0) & 0xFF) / 255.f, \
	.alpha = ((color >> 24) & 0xFF) / 255.f})

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawBitmap(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jlong texture_ptr, jint x, jint y, jint width, jint height, jint color)
{
	GdkSnapshot *snapshot = (GdkSnapshot *)_PTR(snapshot_ptr);
	GdkTexture *texture = GDK_TEXTURE(_PTR(texture_ptr));
	if (color) {  // use only alpha from pixbuf, color is fixed
		graphene_matrix_t color_matrix;
		graphene_vec4_t color_offset;
		graphene_matrix_init_from_float(&color_matrix, (float[]){
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 1,
		});
		graphene_vec4_init(&color_offset, ((color >> 16) & 0xFF) / 255.f, ((color >> 8) & 0xFF) / 255.f, ((color >> 0) & 0xFF) / 255.f, 0);
		gtk_snapshot_push_color_matrix(snapshot, &color_matrix, &color_offset);
	}
	gtk_snapshot_append_texture(snapshot, texture, &GRAPHENE_RECT_INIT(x, y, width, height));
	if (color)
		gtk_snapshot_pop(snapshot);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawRect(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat left, jfloat top, jfloat right, jfloat bottom, jint color)
{
	GdkSnapshot *snapshot = (GdkSnapshot *)_PTR(snapshot_ptr);
	GdkRGBA gdk_color = GDK_RGBA_INIT(color);
	graphene_rect_t bounds = GRAPHENE_RECT_INIT(left, top, right - left, bottom - top);
	gtk_snapshot_append_color(snapshot, &gdk_color, &bounds);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawPath(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jlong path_ptr, jint color, jint style)
{
	GtkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	GskPath *path = _PTR(path_ptr);
	GdkRGBA gdk_color = GDK_RGBA_INIT(color);
	if (style == STYLE_STROKE || style == STYLE_FILL_AND_STROKE) {
		gtk_snapshot_append_stroke(snapshot, path, gsk_stroke_new(2), &gdk_color);
	}
	if (style == STYLE_FILL || style == STYLE_FILL_AND_STROKE) {
		gtk_snapshot_append_fill(snapshot, path, GSK_FILL_RULE_WINDING, &gdk_color);
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

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawLine(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat x0, jfloat y0, jfloat x1, jfloat y1, jint color, jfloat stroke_width)
{
	if (isnan(x0) || isnan(y0) || isnan(x1) || isnan(y1)) {
		return;
	}
	GdkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	GdkRGBA gdk_color = GDK_RGBA_INIT(color);
	gtk_snapshot_save(snapshot);
	gtk_snapshot_translate(snapshot, &GRAPHENE_POINT_INIT(x0, y0));
	float rotation = atan2(y1 - y0, x1 - x0);
	gtk_snapshot_rotate(snapshot, rotation * 180 / M_PI);
	float length = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	gtk_snapshot_append_color(snapshot, &gdk_color, &GRAPHENE_RECT_INIT(0, -stroke_width / 2, length, stroke_width));
	gtk_snapshot_restore(snapshot);
}

extern GtkWidget *window;

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawText(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jstring text, jfloat x, jfloat y, jint color, jfloat text_size)
{
	GdkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	GdkRGBA gdk_color = GDK_RGBA_INIT(color);
	PangoLayout *layout = pango_layout_new(gtk_widget_get_pango_context(window));
	PangoFontDescription *description = pango_font_description_new();
	pango_font_description_set_size(description, text_size * .8f * PANGO_SCALE);
	pango_layout_set_font_description(layout, description);
	const char *str = (*env)->GetStringUTFChars(env, text, NULL);
	pango_layout_set_text(layout, str, -1);
	(*env)->ReleaseStringUTFChars(env, text, str);
	gtk_snapshot_translate(snapshot, &GRAPHENE_POINT_INIT(x, y));
	gtk_snapshot_append_layout(snapshot, layout, &gdk_color);
	gtk_snapshot_translate(snapshot, &GRAPHENE_POINT_INIT(-x, -y));
	g_object_unref(layout);
	g_object_unref(description);
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1drawRoundRect(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat left, jfloat top, jfloat right, jfloat bottom, jfloat rx, jfloat ry, jint color, jfloat width, int style)
{
	GdkSnapshot *snapshot = (GdkSnapshot *)_PTR(snapshot_ptr);
	GdkRGBA gdk_color[4];
	for (int i = 0; i < 4; i++) {
		gdk_color[i].red = (float)((color >> 16) & 0xff) / 0xff;
		gdk_color[i].green = (float)((color >> 8)  & 0xff) / 0xff;
		gdk_color[i].blue = (float)((color >> 0)  & 0xff) / 0xff;
		gdk_color[i].alpha = (float)((color >> 24) & 0xff) / 0xff;
	}
	GskRoundedRect round_rect = {
		.bounds = GRAPHENE_RECT_INIT(left, top, right - left, bottom - top),
		.corner = {{rx, ry}, {rx, ry}, {rx, ry}, {rx, ry}},
	};
	const float widths[4] = {width, width, width, width};
	if (style == STYLE_FILL || style == STYLE_FILL_AND_STROKE) {
		gtk_snapshot_push_rounded_clip(snapshot, &round_rect);
		gtk_snapshot_append_color(snapshot, gdk_color, &round_rect.bounds);
		gtk_snapshot_pop(snapshot);
	}
	if (style == STYLE_STROKE || style == STYLE_FILL_AND_STROKE) {
		gtk_snapshot_append_border(snapshot, &round_rect, widths, gdk_color);
	}
}

JNIEXPORT void JNICALL Java_android_graphics_GskCanvas_native_1scale(JNIEnv *env, jclass this_class, jlong snapshot_ptr, jfloat x, jfloat y)
{
	GdkSnapshot *snapshot = GTK_SNAPSHOT(_PTR(snapshot_ptr));
	gtk_snapshot_scale(snapshot, x, y);
}
