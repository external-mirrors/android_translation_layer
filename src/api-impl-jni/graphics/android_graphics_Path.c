#include "../sk_area/include/c/sk_path.h"
#include <graphene.h>

#include "../defines.h"
#include "../util.h"

#include "../generated_headers/android_graphics_Path.h"
#include "include/c/sk_types.h"

JNIEXPORT jlong JNICALL Java_android_graphics_Path_init1(JNIEnv *env, jclass class)
{
	return _INTPTR(sk_path_new());
}

JNIEXPORT jlong JNICALL Java_android_graphics_Path_init2(JNIEnv *env, jclass class, jlong path_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	return _INTPTR(sk_path_clone(path));
}

JNIEXPORT void JNICALL Java_android_graphics_Path_finalizer(JNIEnv *env, jclass class, jlong path_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	if (path_ptr != -1)
		sk_path_delete(path);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1rCubicTo(JNIEnv *env, jclass class, jlong path_ptr, jfloat x1, jfloat y1, jfloat x2, jfloat y2, jfloat x3, jfloat y3)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_rcubic_to(path, x1, y1, x2, y2, x3, y3);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1rLineTo(JNIEnv *env, jclass class, jlong path_ptr, jfloat x, jfloat y)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_rline_to(path, x, y);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1cubicTo(JNIEnv *env, jclass class, jlong path_ptr, jfloat x1, jfloat y1, jfloat x2, jfloat y2, jfloat x3, jfloat y3)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_cubic_to(path, x1, y1, x2, y2, x3, y3);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1addPath__JJJ(JNIEnv *env, jclass class, jlong path_ptr, jlong src_ptr, jlong matrix)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_t *src = (sk_path_t *)_PTR(src_ptr);
	sk_path_add_path(path, src, APPEND_SK_PATH_ADD_MODE);
}

JNIEXPORT jint JNICALL Java_android_graphics_Path_native_1getFillType(JNIEnv *env, jclass class, jlong path_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	return sk_path_get_filltype(path);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1reset(JNIEnv *env, jclass class, jlong path_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_reset(path);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1setFillType(JNIEnv *env, jclass class, jlong path_ptr, jint ft)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_set_filltype(path, ft);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1moveTo(JNIEnv *env, jclass class, jlong path_ptr, jfloat x, jfloat y)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_move_to(path, x, y);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1close(JNIEnv *env, jclass class, jlong path_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_close(path);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1lineTo(JNIEnv *env, jclass class, jlong path_ptr, jfloat x, jfloat y)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_line_to(path, x, y);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1rewind(JNIEnv *env, jclass class, jlong path_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_rewind(path);
}

JNIEXPORT jboolean JNICALL Java_android_graphics_Path_native_1isEmpty(JNIEnv *env, jclass class, jlong path_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	return !sk_path_count_points(path) && !sk_path_count_verbs(path);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1computeBounds(JNIEnv *env, jclass class, jlong path_ptr, jobject rect)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_rect_t bounds;
	sk_path_get_bounds(path, &bounds);
	_SET_FLOAT_FIELD(rect, "left", bounds.left);
	_SET_FLOAT_FIELD(rect, "top", bounds.top);
	_SET_FLOAT_FIELD(rect, "right", bounds.right);
	_SET_FLOAT_FIELD(rect, "bottom", bounds.bottom);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1arcTo(JNIEnv *env, jclass class, jlong path_ptr, jobject oval, jfloat startAngle, jfloat sweepAngle, jboolean forceMoveTo)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	float left = _GET_FLOAT_FIELD(oval, "left");
	float top = _GET_FLOAT_FIELD(oval, "top");
	float right = _GET_FLOAT_FIELD(oval, "right");
	float bottom = _GET_FLOAT_FIELD(oval, "bottom");
	sk_path_arc_to_with_oval(path, &(sk_rect_t){left, top, right, bottom}, startAngle, sweepAngle, forceMoveTo);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1addRect__JLandroid_graphics_RectF_2I(JNIEnv *env, jclass class, jlong path_ptr, jobject rect, jint dir)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	float left = _GET_FLOAT_FIELD(rect, "left");
	float top = _GET_FLOAT_FIELD(rect, "top");
	float right = _GET_FLOAT_FIELD(rect, "right");
	float bottom = _GET_FLOAT_FIELD(rect, "bottom");
	sk_path_add_rect(path, &(sk_rect_t){left, top, right, bottom}, (sk_path_direction_t)dir);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1transform__JJ(JNIEnv *env, jclass class, jlong path_ptr, jlong matrix_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	graphene_matrix_t *matrix = (graphene_matrix_t *)_PTR(matrix_ptr);
	float v[16];
	graphene_matrix_to_float(matrix, v);
	sk_matrix_t m = {v[0], v[4], v[12],
	                 v[1], v[5], v[13],
	                 v[3], v[7], v[15]};
	sk_path_transform(path, &m);
}

JNIEXPORT jboolean JNICALL Java_android_graphics_Path_native_1op(JNIEnv *env, jclass class, jlong path_ptr, jlong other_ptr, jint op, jlong result_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_t *other = (sk_path_t *)_PTR(other_ptr);
	sk_path_t *result = (sk_path_t *)_PTR(result_ptr);
	return sk_pathop_op(path, other, (sk_pathop_t)op, result);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1quadTo(JNIEnv *env, jclass class, jlong path_ptr, jfloat x1, jfloat y1, jfloat x2, jfloat y2)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_quad_to(path, x1, y1, x2, y2);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1rQuadTo(JNIEnv *env, jclass class, jlong path_ptr, jfloat dx1, jfloat dy1, jfloat dx2, jfloat dy2)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_rquad_to(path, dx1, dy1, dx2, dy2);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1rMoveTo(JNIEnv *env, jclass class, jlong path_ptr, jfloat dx, jfloat dy)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_rmove_to(path, dx, dy);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1addRoundRect__JLandroid_graphics_RectF_2_3FI(JNIEnv *env, jclass class, jlong path_ptr, jobject rect, jfloatArray radii, jint dir)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	float left = _GET_FLOAT_FIELD(rect, "left");
	float top = _GET_FLOAT_FIELD(rect, "top");
	float right = _GET_FLOAT_FIELD(rect, "right");
	float bottom = _GET_FLOAT_FIELD(rect, "bottom");
	jfloat *radii_array = (*env)->GetFloatArrayElements(env, radii, 0);
	sk_path_add_rounded_rect(path, &(sk_rect_t){left, top, right, bottom}, radii_array[0], radii_array[1], (sk_path_direction_t)dir);
	(*env)->ReleaseFloatArrayElements(env, radii, radii_array, 0);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1addOval(JNIEnv *env, jclass class, jlong path_ptr, jobject rect, jint dir)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	float left = _GET_FLOAT_FIELD(rect, "left");
	float top = _GET_FLOAT_FIELD(rect, "top");
	float right = _GET_FLOAT_FIELD(rect, "right");
	float bottom = _GET_FLOAT_FIELD(rect, "bottom");
	sk_path_add_oval(path, &(sk_rect_t){left, top, right, bottom}, (sk_path_direction_t)dir);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1addCircle(JNIEnv *env, jclass class, jlong path_ptr, jfloat x, jfloat y, jfloat radius, jint dir)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_add_circle(path, x, y, radius, (sk_path_direction_t)dir);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1addPath__JJ(JNIEnv *env, jclass class, jlong path_ptr, jlong src_ptr)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_t *src = (sk_path_t *)_PTR(src_ptr);
	sk_path_add_path(path, src, APPEND_SK_PATH_ADD_MODE);
}

JNIEXPORT void JNICALL Java_android_graphics_Path_native_1addPath__JJFF(JNIEnv *env, jclass class, jlong path_ptr, jlong src_ptr, jfloat dx, jfloat dy)
{
	sk_path_t *path = (sk_path_t *)_PTR(path_ptr);
	sk_path_t *src = (sk_path_t *)_PTR(src_ptr);
	sk_path_add_path_offset(path, src, dx, dy, APPEND_SK_PATH_ADD_MODE);
}
