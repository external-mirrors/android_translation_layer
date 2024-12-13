#include <gtk/gtk.h>

#include "defines.h"
#include "util.h"

#include "../sk_area/include/c/sk_canvas.h"
#include "../sk_area/include/c/sk_font.h"
#include "../sk_area/include/c/sk_image.h"
#include "../sk_area/include/c/sk_typeface.h"
#include "../sk_area/include/c/sk_types.h"

#include "generated_headers/android_graphics_Canvas.h"

JNIEXPORT jlong JNICALL Java_android_graphics_Canvas_native_1canvas_1from_1bitmap(JNIEnv *env, jclass this, jlong _pixbuf)
{
	GdkPixbuf *pixbuf = (GdkPixbuf *)_PTR(_pixbuf);

	/* - copied from bitmap (TODO: refactor) - */
	sk_imageinfo_t info = {
		.width = gdk_pixbuf_get_width(pixbuf),
		.height = gdk_pixbuf_get_height(pixbuf),
		.colorType = RGBA_8888_SK_COLORTYPE, // is this correct?
		.alphaType = PREMUL_SK_ALPHATYPE,
	};
	void *pixbuf_pixels = gdk_pixbuf_get_pixels(pixbuf);
	int rowstride = gdk_pixbuf_get_rowstride(pixbuf);
//	size_t pixbuf_size = rowstride * (info.height - 1)
//	                     + /* last row: */ info.width * ((gdk_pixbuf_get_n_channels(pixbuf) * gdk_pixbuf_get_bits_per_sample(pixbuf) + 7) / 8);
	/* --------------------------------------- */

	return _INTPTR(sk_canvas_new_from_raster(&info, pixbuf_pixels, /*pixbuf_size*/rowstride, NULL));
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1save(JNIEnv *env, jclass this, jlong skia_canvas, jlong widget)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);

	sk_canvas_save(canvas);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1restore(JNIEnv *env, jclass this, jlong skia_canvas, jlong widget)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);

	sk_canvas_restore(canvas);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1drawLine(JNIEnv *env, jclass this_class, jlong skia_canvas, jlong widget, jfloat start_x, jfloat start_y, jfloat stop_x, jfloat stop_y, jlong skia_paint)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);

	sk_canvas_draw_line(canvas, start_x, start_y, stop_x, stop_y, paint);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1drawBitmap(JNIEnv *env , jclass this_class, jlong skia_canvas, jlong widget, jlong _pixbuf,
                                                                       jfloat src_left, jfloat src_top, jfloat src_right, jfloat src_bottom,
                                                                       jfloat dst_left, jfloat dst_top, jfloat dst_right, jfloat dst_bottom,
                                                                       jlong skia_paint)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);
	GdkPixbuf *pixbuf = (GdkPixbuf *)_PTR(_pixbuf);
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);

	sk_image_t *image = g_object_get_data(G_OBJECT(pixbuf), "sk_image");
	if(!image) {
		fprintf(stderr, "drawBitmap: pixbuf doesn't have a skia image associated: %p\n", pixbuf);
		return;
	}
	sk_canvas_draw_image_rect(canvas, image, &(sk_rect_t){src_left, src_top, src_right, src_bottom},
	                                    &(sk_rect_t){dst_left, dst_top, dst_right, dst_bottom}, paint);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1drawRect(JNIEnv *env, jclass this, jlong skia_canvas, jfloat left, jfloat top, jfloat right, jfloat bottom, jlong skia_paint)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);

	sk_canvas_draw_rect(canvas, &(sk_rect_t){left, top, right, bottom}, paint);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1drawText(JNIEnv *env, jclass this, jlong skia_canvas, jobject _text, jint start, jint end, jfloat x, jfloat y, jlong skia_font, jlong skia_paint)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);
	sk_font_t *font = _PTR(skia_font);

	const char *text = _CSTRING(_text);

	sk_canvas_draw_simple_text(canvas, text + start, end - start, UTF8_SK_TEXT_ENCODING, x, y, font, paint);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1rotate(JNIEnv *env, jclass this, jlong skia_canvas, jlong widget, jfloat angle)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);

	sk_canvas_rotate_degrees(canvas, angle);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1rotate_1and_1translate(JNIEnv *env, jclass this, jlong skia_canvas, jlong widget, jfloat angle, jfloat tx, jfloat ty)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);

	sk_canvas_translate(canvas, tx, ty);
	sk_canvas_rotate_degrees(canvas, angle);
	sk_canvas_translate(canvas, -tx, -ty);

}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1drawPath(JNIEnv *env, jclass class, jlong skia_canvas, jlong path_ptr, jlong skia_paint)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);

	sk_canvas_draw_path(canvas, path, paint);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1destroy_1canvas(JNIEnv *env, jclass class, jlong skia_canvas)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);
	sk_canvas_destroy(canvas);
}

JNIEXPORT void JNICALL Java_android_graphics_Canvas_native_1scale(JNIEnv *env, jclass class, jlong skia_canvas, jfloat sx, jfloat sy)
{
	sk_canvas_t *canvas = (sk_canvas_t *)_PTR(skia_canvas);
	sk_canvas_scale(canvas, sx, sy);
}
