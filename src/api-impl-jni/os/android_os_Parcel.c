#include <glib.h>

#include "../defines.h"

#include "../generated_headers/android_os_Parcel.h"

JNIEXPORT void JNICALL Java_android_os_Parcel_native_1writeInt(JNIEnv *env, jclass clazz, jlong builder_ptr, jint value)
{
	GVariantBuilder *builder = (GVariantBuilder *)builder_ptr;
	if (builder)
		g_variant_builder_add(builder, "i", value);
}

JNIEXPORT void JNICALL Java_android_os_Parcel_native_1writeString(JNIEnv *env, jclass clazz, jlong builder_ptr, jstring value)
{
	GVariantBuilder *builder = (GVariantBuilder *)builder_ptr;
	if (builder)
		g_variant_builder_add(builder, "s", (*env)->GetStringUTFChars(env, value, NULL));
}

JNIEXPORT jint JNICALL Java_android_os_Parcel_native_1readInt(JNIEnv *env, jclass clazz, jlong iter_ptr)
{
	GVariantIter *iter = (GVariantIter *)iter_ptr;
	jint i = 0;
	if (iter)
		g_variant_iter_next(iter, "i", &i);
	return i;
}

JNIEXPORT jstring JNICALL Java_android_os_Parcel_native_1readString(JNIEnv *env, jclass clazz, jlong iter_ptr)
{
	GVariantIter *iter = (GVariantIter *)iter_ptr;
	const char *s = NULL;
	if (iter)
		g_variant_iter_next(iter, "s", &s);
	return s ? _JSTRING(s) : NULL;
}
