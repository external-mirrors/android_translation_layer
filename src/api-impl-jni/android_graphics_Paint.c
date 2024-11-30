#include <gtk/gtk.h>

#include "defines.h"
#include "util.h"

#include "../sk_area/include/c/sk_font.h"
#include "../sk_area/include/c/sk_paint.h"
#include "../sk_area/include/c/sk_typeface.h"
#include "generated_headers/android_graphics_Paint.h"

JNIEXPORT jlong JNICALL Java_android_graphics_Paint_native_1constructor(JNIEnv *env, jobject this)
{
	return _INTPTR(sk_paint_new());
}

JNIEXPORT void JNICALL Java_android_graphics_Paint_native_1set_1antialias(JNIEnv *env, jobject this, jlong skia_paint, jboolean aa)
{
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);

	sk_paint_set_antialias(paint, aa);
}

/* NOTE: sk_color_t seems to have the same internal representation as android uses for color, so we just pass that directly */
JNIEXPORT void JNICALL Java_android_graphics_Paint_native_1set_1color(JNIEnv *env, jobject this, jlong skia_paint, jint color)
{
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);

	sk_paint_set_color(paint, color);
}

JNIEXPORT jint JNICALL Java_android_graphics_Paint_native_1get_1color(JNIEnv *env, jobject this, jlong skia_paint)
{
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);

	return sk_paint_get_color(paint);
}

JNIEXPORT jlong JNICALL Java_android_graphics_Paint_native_1create_1font(JNIEnv *env, jclass this)
{
	return _INTPTR(sk_font_new()); /* TODO: recycle this */
}

JNIEXPORT void JNICALL Java_android_graphics_Paint_native_1set_1typeface(JNIEnv *env, jclass this, jlong skia_font, jlong skia_typeface)
{
	sk_font_t *font = _PTR(skia_font);
	sk_typeface_t *typeface = _PTR(skia_typeface);

	sk_font_set_typeface(font, typeface);
}

JNIEXPORT void JNICALL Java_android_graphics_Paint_native_1set_1text_1size(JNIEnv *env, jclass this, jlong skia_font, jfloat size)
{
	sk_font_t *font = _PTR(skia_font);

	sk_font_set_size(font, size);
}

JNIEXPORT jfloat JNICALL Java_android_graphics_Paint_native_1ascent(JNIEnv *env, jclass this, jlong skia_font)
{
	sk_font_t *font = _PTR(skia_font);

	sk_fontmetrics_t metrics;
	sk_font_get_metrics(font, &metrics);

	return metrics.fAscent;
}

JNIEXPORT jfloat JNICALL Java_android_graphics_Paint_native_1measure_1text(JNIEnv *env, jclass this, jlong skia_font, jobject _text, jint start, jint end, jlong skia_paint)
{
	sk_font_t *font = _PTR(skia_font);
	sk_paint_t *paint = (sk_paint_t *)_PTR(skia_paint);

	const char *text = _CSTRING(_text);

	return sk_font_measure_text(font, text + start, end - start, UTF8_SK_TEXT_ENCODING, NULL, paint);
}

JNIEXPORT void JNICALL Java_android_graphics_Paint_native_1set_1stroke_1width(JNIEnv *env, jclass this, jlong skia_paint, jfloat width)
{
	sk_paint_set_stroke_width(_PTR(skia_paint), width);
}

JNIEXPORT jfloat JNICALL Java_android_graphics_Paint_native_1get_1stroke_1width(JNIEnv *env, jclass this, jlong skia_paint)
{
	return sk_paint_get_stroke_width(_PTR(skia_paint));
}

JNIEXPORT void JNICALL Java_android_graphics_Paint_native_1set_1style(JNIEnv *env, jclass this, jlong skia_paint, jint style)
{
	sk_paint_set_style(_PTR(skia_paint), (sk_paint_style_t)style);
}

JNIEXPORT void JNICALL Java_android_graphics_Paint_native_1set_1blendmode(JNIEnv *env, jclass this, jlong skia_paint, jint blendmode)
{
	sk_paint_set_blendmode(_PTR(skia_paint), (sk_blendmode_t)blendmode);
}
