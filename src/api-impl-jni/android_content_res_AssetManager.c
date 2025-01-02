#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <androidfw/androidfw_c_api.h>

#include "defines.h"
#include "util.h"
#include "generated_headers/android_content_res_AssetManager.h"

#include <glib.h>
#include <dirent.h>

#define JAVA_ENUM_CLASS android_content_res_AssetManager
enum {
	JAVA_ENUM(STYLE_TYPE),
	JAVA_ENUM(STYLE_DATA),
	JAVA_ENUM(STYLE_ASSET_COOKIE),
	JAVA_ENUM(STYLE_RESOURCE_ID),
	JAVA_ENUM(STYLE_CHANGING_CONFIGURATIONS),
	JAVA_ENUM(STYLE_DENSITY),
	JAVA_ENUM(STYLE_NUM_ENTRIES),
};
#undef JAVA_ENUM_CLASS

#define ASSET_DIR "assets/"
char *get_app_data_dir();

JNIEXPORT jlong JNICALL Java_android_content_res_AssetManager_openAsset(JNIEnv *env, jobject this, jstring _file_name, jint mode)
{
	const char *file_name = _CSTRING(_file_name);

	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	struct Asset *asset = AssetManager_openNonAsset(asset_manager, file_name, mode);
	android_log_printf(ANDROID_LOG_VERBOSE, "["__FILE__"]", "AssetManager_openAsset(%p, %s, %d) returns %p\n", asset_manager, file_name, mode, asset);

	return _INTPTR(asset);
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_openAssetFd(JNIEnv *env, jobject this, jstring _file_name, jint mode, jlongArray _offset, jlongArray _size)
{
	int fd;
	off_t offset;
	off_t size;

	const char *file_name = _CSTRING(_file_name);

	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	struct Asset *asset = AssetManager_openNonAsset(asset_manager, file_name, mode);
	android_log_printf(ANDROID_LOG_VERBOSE, "["__FILE__"]", "AssetManager_openAssetFd(%p, %s, %d, ...)\n", asset_manager, file_name, mode);

	fd = Asset_openFileDescriptor(asset, &offset, &size);

	(*env)->SetLongArrayRegion(env, _offset, 0, 1, (jlong[]){offset});
	(*env)->SetLongArrayRegion(env, _size, 0, 1, (jlong[]){size});

	return fd;
}

JNIEXPORT jlong JNICALL Java_android_content_res_AssetManager_getAssetLength(JNIEnv *env, jobject this, jlong _asset)
{
	struct Asset *asset = _PTR(_asset);
	return Asset_getLength(asset);
}

JNIEXPORT jlong JNICALL Java_android_content_res_AssetManager_getAssetRemainingLength(JNIEnv *env, jobject this, jlong _asset)
{
	struct Asset *asset = _PTR(_asset);
	return Asset_getRemainingLength(asset);
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_readAsset(JNIEnv *env, jobject this, jlong _asset, jbyteArray b, jlong offset, jlong length)
{
	int ret;

	struct Asset *asset = _PTR(_asset);
	jbyte *array = _GET_BYTE_ARRAY_ELEMENTS(b);
	ret = Asset_read(asset, &array[offset], length);
	_RELEASE_BYTE_ARRAY_ELEMENTS(b, array);

	return ret;
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_readAssetChar(JNIEnv *env, jobject this, jlong _asset)
{
	int ret;
	uint8_t byte;

	struct Asset *asset = _PTR(_asset);
	ret = Asset_read(asset, &byte, 1);
	return (ret == 1) ? byte : -1;
}

JNIEXPORT jlong JNICALL Java_android_content_res_AssetManager_seekAsset(JNIEnv *env, jobject this, jlong _asset, jlong offset, jint whence)
{
	struct Asset *asset = _PTR(_asset);
	return Asset_seek(asset, offset, whence);
}

JNIEXPORT void JNICALL Java_android_content_res_AssetManager_destroyAsset(JNIEnv *env, jobject this, jlong _asset)
{
	struct Asset *asset = _PTR(_asset);
	Asset_delete(asset);
}

JNIEXPORT void JNICALL Java_android_content_res_AssetManager_init(JNIEnv *env, jobject this)
{
	struct AssetManager *asset_manager = AssetManager_new();
	const struct ResTable_config config = {
		.density = /*ACONFIGURATION_DENSITY_MEDIUM*/ 160,
		.sdkVersion = 24,
	};
	AssetManager_setConfiguration(asset_manager, &config, NULL);
	_SET_LONG_FIELD(this, "mObject", _INTPTR(asset_manager));
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_addAssetPathNative(JNIEnv *env, jobject this, jstring path)
{
	int32_t cookie;
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	AssetManager_addAssetPath(asset_manager, _CSTRING(path), &cookie, false, false);
	return cookie;
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_loadResourceValue(JNIEnv *env, jobject this, jint ident, jshort density, jobject outValue, jboolean resolve)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	uint32_t resId = ident;
	struct Res_value value;
	uint32_t outSpecFlags;
	struct ResTable_config outConfig;
	ssize_t block = ResTable_getResource(res_table, resId, &value, false, density, &outSpecFlags, &outConfig);
	if (resolve) {
		block = ResTable_resolveReference(res_table, &value, block, &resId, &outSpecFlags, &outConfig);
	}
	if (block >= 0) {
		_SET_INT_FIELD(outValue, "type", value.dataType);
		_SET_INT_FIELD(outValue, "data", value.data);
		_SET_INT_FIELD(outValue, "resourceId", resId);
		_SET_INT_FIELD(outValue, "assetCookie", block);
		if (value.dataType == TYPE_STRING) {
			const struct ResStringPool *string_pool = ResTable_getTableStringBlock(res_table, block);
			size_t len;
			const char16_t *string = ResStringPool_stringAt(string_pool, value.data, &len);
			_SET_OBJ_FIELD(outValue, "string", "Ljava/lang/CharSequence;", (*env)->NewString(env, string, len));
		} else {
			_SET_OBJ_FIELD(outValue, "string", "Ljava/lang/CharSequence;", NULL);
		}
	}
	return block;
}

JNIEXPORT jobjectArray JNICALL Java_android_content_res_AssetManager_getArrayStringResource(JNIEnv *env, jobject this, jint ident)
{
	int i;
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	const struct bag_entry *bag;
	int bag_count = ResTable_lockBag(res_table, ident, &bag);
	jobjectArray array = (*env)->NewObjectArray(env, bag_count, (*env)->FindClass(env, "java/lang/String"), NULL);
	for (i = 0; i < bag_count; i++) {
		struct Res_value value = bag[i].map.value;
		ssize_t block = ResTable_resolveReference(res_table, &value, bag[i].stringBlock, NULL, NULL, NULL);
		if (value.dataType == TYPE_STRING) {
			const struct ResStringPool *string_pool = ResTable_getTableStringBlock(res_table, block);
			if (string_pool == NULL)
				continue;
			size_t len;
			const char16_t *string = ResStringPool_stringAt(string_pool, value.data, &len);
			(*env)->SetObjectArrayElement(env, array, i, (*env)->NewString(env, string, len));
		}
	}

	ResTable_unlockBag(res_table, bag);
	return array;
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_getResourceIdentifier(JNIEnv *env, jobject this, jstring name, jstring defType, jstring defPackage)
{
	const char16_t *name16 = NULL;
	const char16_t *defType16 = NULL;
	const char16_t *defPackage16 = NULL;
	int name_len = 0;
	int defType_len = 0;
	int defPackage_len = 0;
	int ret;

	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	if (name) {
		name16 = (*env)->GetStringChars(env, name, NULL);
		name_len = (*env)->GetStringLength(env, name);
	}
	if (defType) {
		defType16 = (*env)->GetStringChars(env, defType, NULL);
		defType_len = (*env)->GetStringLength(env, defType);
	}
	if (defPackage) {
		defPackage16 = (*env)->GetStringChars(env, defPackage, NULL);
		defPackage_len = (*env)->GetStringLength(env, defPackage);
	}
	ret = ResTable_identifierForName(res_table, name16, name_len, defType16, defType_len, defPackage16, defPackage_len, NULL);
	if (name)
		(*env)->ReleaseStringChars(env, name, name16);
	if (defType)
		(*env)->ReleaseStringChars(env, defType, defType16);
	if (defPackage)
		(*env)->ReleaseStringChars(env, defPackage, defPackage16);
	return ret;
}

JNIEXPORT jobject JNICALL Java_android_content_res_AssetManager_getPooledString(JNIEnv *env, jobject this, jint block, jint index)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	const struct ResStringPool *string_pool = ResTable_getTableStringBlock(res_table, block);
	size_t len;
	const char16_t *string = ResStringPool_stringAt(string_pool, index, &len);
	return (*env)->NewString(env, string, len);
}

JNIEXPORT jlong JNICALL Java_android_content_res_AssetManager_newTheme(JNIEnv *env, jobject this)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	struct Theme *theme = Theme_new(AssetManager_getResources(asset_manager, true));
	return _INTPTR(theme);
}

JNIEXPORT void JNICALL Java_android_content_res_AssetManager_deleteTheme(JNIEnv *env, jobject this, jlong theme_ptr)
{
	Theme_delete(_PTR(theme_ptr));
}

JNIEXPORT void JNICALL Java_android_content_res_AssetManager_applyThemeStyle(JNIEnv *env, jobject this, jlong theme_ptr, jint styleRes, jboolean force)
{
	Theme_applyStyle(_PTR(theme_ptr), styleRes, force);
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_loadThemeAttributeValue(JNIEnv *env, jobject this, jlong theme_ptr, jint ident, jobject outValue, jboolean resolve)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	struct Theme *theme = _PTR(theme_ptr);
	uint32_t resId = 0;
	struct Res_value value;
	uint32_t outSpecFlags;
	struct ResTable_config outConfig;
	int block = Theme_getAttribute(theme, ident, &value, &outSpecFlags);
	if (resolve) {
		block = Theme_resolveAttributeReference(theme, &value, block, &resId, &outSpecFlags, &outConfig);
	}
	if (block >= 0) {
		_SET_INT_FIELD(outValue, "type", value.dataType);
		_SET_INT_FIELD(outValue, "data", value.data);
		_SET_INT_FIELD(outValue, "resourceId", resId);
		_SET_INT_FIELD(outValue, "assetCookie", block);
		if (value.dataType == TYPE_STRING) {
			const struct ResStringPool *string_pool = ResTable_getTableStringBlock(res_table, block);
			size_t len;
			const char16_t *string = ResStringPool_stringAt(string_pool, value.data, &len);
			_SET_OBJ_FIELD(outValue, "string", "Ljava/lang/CharSequence;", (*env)->NewString(env, string, len));
		} else {
			_SET_OBJ_FIELD(outValue, "string", "Ljava/lang/CharSequence;", NULL);
		}
	}
	return block;
}

/* function ported from AOSP - Copyright 2006, The Android Open Source Project */
JNIEXPORT jboolean JNICALL Java_android_content_res_AssetManager_resolveAttrs(JNIEnv *env, jclass this,
                                                                              jlong theme_ptr, jint def_style_attr,
                                                                              jint def_style_res, jintArray java_values,
                                                                              jintArray java_attrs, jintArray out_java_values,
                                                                              jintArray out_java_indices)
{
	struct Theme *theme = _PTR(theme_ptr);
	const jsize attrs_len = (*env)->GetArrayLength(env, java_attrs);
	const jsize out_values_len = (*env)->GetArrayLength(env, out_java_values);
	if (out_values_len < (attrs_len * STYLE_NUM_ENTRIES)) {
		(*env)->ThrowNew(env, (*env)->FindClass(env, "java/lang/IndexOutOfBoundsException"), "outValues too small");
		return false;
	}

	jint *attrs = (jint *)(*env)->GetPrimitiveArrayCritical(env, java_attrs, NULL);
	if (attrs == NULL) {
		return true;
	}

	jint *values = NULL;
	jsize values_len = 0;
	if (java_values != NULL) {
		values_len = (*env)->GetArrayLength(env, java_values);
		values = (jint *)(*env)->GetPrimitiveArrayCritical(env, java_values, NULL);
		if (values == NULL) {
			(*env)->ReleasePrimitiveArrayCritical(env, java_attrs, attrs, JNI_ABORT);
			return false;
		}
	}

	jint *out_values = (jint *)(*env)->GetPrimitiveArrayCritical(env, out_java_values, NULL);
	if (!out_values) {
		(*env)->ReleasePrimitiveArrayCritical(env, java_attrs, attrs, JNI_ABORT);
		if (values) {
			(*env)->ReleasePrimitiveArrayCritical(env, java_values, values, JNI_ABORT);
		}
		return false;
	}

	jint *out_indices = NULL;
	if (out_java_indices) {
		jsize out_indices_len = (*env)->GetArrayLength(env, out_java_indices);
		if (out_indices_len > attrs_len) {
			out_indices = (jint *)(*env)->GetPrimitiveArrayCritical(env, out_java_indices, NULL);
			if (!out_indices) {
				(*env)->ReleasePrimitiveArrayCritical(env, java_attrs, attrs, JNI_ABORT);
				if (values)
					(*env)->ReleasePrimitiveArrayCritical(env, java_values, values, JNI_ABORT);
				(*env)->ReleasePrimitiveArrayCritical(env, out_java_values, out_values, JNI_ABORT);
				return false;
			}
		}
	}

	bool ret = ResolveAttrs(theme, def_style_attr, def_style_res,
	                        (uint32_t *)values, values_len,
	                        (uint32_t *)attrs, attrs_len,
	                        (uint32_t *)out_values, (uint32_t *)out_indices);
	if (out_indices)
		(*env)->ReleasePrimitiveArrayCritical(env, out_java_indices, out_indices, 0);

	(*env)->ReleasePrimitiveArrayCritical(env, out_java_values, out_values, 0);

	if (values)
		(*env)->ReleasePrimitiveArrayCritical(env, java_values, values, JNI_ABORT);

	(*env)->ReleasePrimitiveArrayCritical(env, java_attrs, attrs, JNI_ABORT);
	return ret;
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_getArraySize(JNIEnv *env, jobject this, jint ident)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	const struct bag_entry *bag;
	int bag_count = ResTable_lockBag(res_table, ident, &bag);
	ResTable_unlockBag(res_table, bag);
	return bag_count;
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_retrieveArray(JNIEnv *env, jobject this, jint ident, jintArray outArray)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	const struct bag_entry *bag;
	int i;

	jint *array = (*env)->GetIntArrayElements(env, outArray, NULL);
	int bag_count = ResTable_lockBag(res_table, ident, &bag);
	for (i = 0; i < bag_count; i++) {
		struct Res_value value = bag[i].map.value;
		uint32_t resId = 0;
		ssize_t block = ResTable_resolveReference(res_table, &value, bag[i].stringBlock, &resId, NULL, NULL);

		array[i*STYLE_NUM_ENTRIES + STYLE_TYPE] = value.dataType;
		array[i*STYLE_NUM_ENTRIES + STYLE_DATA] = value.data;
		array[i*STYLE_NUM_ENTRIES + STYLE_ASSET_COOKIE] = block;
		array[i*STYLE_NUM_ENTRIES + STYLE_RESOURCE_ID] = resId;

	}
	ResTable_unlockBag(res_table, bag);
	(*env)->ReleaseIntArrayElements(env, outArray, array, 0);
	return bag_count;
}

JNIEXPORT jstring JNICALL Java_android_content_res_AssetManager_getResourcePackageName(JNIEnv *env, jobject this, jint ident)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	struct resource_name res_name;
	bool ret = ResTable_getResourceName(res_table, ident, false, &res_name);
	return (ret && res_name.package) ? (*env)->NewString(env, res_name.package, res_name.packageLen) : NULL;
}

JNIEXPORT jstring JNICALL Java_android_content_res_AssetManager_getResourceTypeName(JNIEnv *env, jobject this, jint ident)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	struct resource_name res_name;
	bool ret = ResTable_getResourceName(res_table, ident, false, &res_name);
	return (ret && res_name.type) ? (*env)->NewString(env, res_name.type, res_name.typeLen) : NULL;
}

JNIEXPORT jstring JNICALL Java_android_content_res_AssetManager_getResourceEntryName(JNIEnv *env, jobject this, jint ident)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	struct resource_name res_name;
	bool ret = ResTable_getResourceName(res_table, ident, false, &res_name);
	return (ret && res_name.name) ? (*env)->NewString(env, res_name.name, res_name.nameLen) : NULL;
}

JNIEXPORT jint JNICALL Java_android_content_res_AssetManager_loadResourceBagValue(JNIEnv *env, jobject this, jint ident, jint bagEntryId, jobject outValue, jboolean resolve)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable *res_table = AssetManager_getResources(asset_manager, true);
	const struct bag_entry *bag;
	int i;
	ssize_t block = -1;

	int bag_count = ResTable_lockBag(res_table, ident, &bag);
	for (i = 0; i < bag_count; i++) {
		if (bag[i].map.name.ident == bagEntryId) {
			struct Res_value value = bag[i].map.value;
			uint32_t resId = 0;
			block = ResTable_resolveReference(res_table, &value, bag[i].stringBlock, &resId, NULL, NULL);

			_SET_INT_FIELD(outValue, "type", value.dataType);
			_SET_INT_FIELD(outValue, "data", value.data);
			_SET_INT_FIELD(outValue, "resourceId", resId);
			_SET_INT_FIELD(outValue, "assetCookie", block);
			if (value.dataType == TYPE_STRING) {
				const struct ResStringPool *string_pool = ResTable_getTableStringBlock(res_table, block);
				size_t len;
				const char16_t *string = ResStringPool_stringAt(string_pool, value.data, &len);
				_SET_OBJ_FIELD(outValue, "string", "Ljava/lang/CharSequence;", (*env)->NewString(env, string, len));
			} else {
				_SET_OBJ_FIELD(outValue, "string", "Ljava/lang/CharSequence;", NULL);
			}
			break;
		}
	}

	ResTable_unlockBag(res_table, bag);
	return block;
}

JNIEXPORT void JNICALL Java_android_content_res_AssetManager_copyTheme(JNIEnv *env, jclass class, jlong dest, jlong src)
{
	Theme_setTo(_PTR(dest), _PTR(src));
}

JNIEXPORT void JNICALL Java_android_content_res_AssetManager_setConfiguration(
    JNIEnv *env, jobject this, jint mcc, jint mnc, jstring locale,
    jint orientation, jint touchscreen, jint density, jint keyboard,
    jint keyboardHidden, jint navigation, jint screenWidth, jint screenHeight,
    jint smallestScreenWidthDp, jint screenWidthDp, jint screenHeightDp,
    jint screenLayout, jint uiMode, jint majorVersion)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const struct ResTable_config config = {
		.mcc = mcc,
		.mnc = mnc,
		.orientation = orientation,
		.touchscreen = touchscreen,
		.density = density,
		.keyboard = keyboard,
		.navigation = navigation,
		.screenWidth = screenWidth,
		.screenHeight = screenHeight,
		.smallestScreenWidthDp = smallestScreenWidthDp,
		.screenWidthDp = screenWidthDp,
		.screenHeightDp = screenHeightDp,
		.screenLayout = screenLayout,
		.uiMode = uiMode,
		.sdkVersion = majorVersion
	};
	AssetManager_setConfiguration(asset_manager, &config, NULL);
}

JNIEXPORT jobjectArray JNICALL Java_android_content_res_AssetManager_list(JNIEnv *env, jobject this, jstring _path)
{
	DIR *d;
	struct dirent *dir;

	const char* path_rel = _CSTRING(_path);
	char *app_data_dir = get_app_data_dir();
	char *path_abs = malloc(strlen(app_data_dir) + strlen(ASSET_DIR) + strlen(path_rel) + 1);

	strcpy(path_abs, app_data_dir);
	strcat(path_abs, ASSET_DIR);
	strcat(path_abs, path_rel);

	d = opendir(path_abs);

	GArray *assets = g_array_new(false, false, sizeof(const char *));
	int i = 0;
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			char *asset_path = malloc (strlen(dir->d_name) + 1);
			strcpy(asset_path, dir->d_name);
			g_array_append_val (assets, asset_path);
		}
		closedir(d);
	}

	jobjectArray array = (*env)->NewObjectArray(env, assets->len, (*env)->FindClass(env, "java/lang/String"), NULL);
	for (i = 0; i < assets->len; i++)
	{
		const char *asset = g_array_index(assets, const char *, i);
		(*env)->SetObjectArrayElement(env, array, i, (*env)->NewStringUTF(env, asset));
	}

	g_array_free(assets, TRUE);

	return array;
}

JNIEXPORT jlong JNICALL Java_android_content_res_AssetManager_openXmlAssetNative(JNIEnv *env, jobject this, jint cookie, jstring _file_name)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	const char *file_name = (*env)->GetStringUTFChars(env, _file_name, NULL);
	struct Asset *asset = AssetManager_openNonAsset(asset_manager, file_name, ACCESS_BUFFER);
	(*env)->ReleaseStringUTFChars(env, _file_name, file_name);

	struct ResXMLTree *res_xml = ResXMLTree_new();
	ResXMLTree_setTo(res_xml, Asset_getBuffer(asset, true), Asset_getLength(asset), true);
	Asset_delete(asset);
	return _INTPTR(res_xml);
}

JNIEXPORT jobjectArray JNICALL Java_android_content_res_AssetManager_getLocales(JNIEnv *env, jobject this)
{
	struct AssetManager *asset_manager = _PTR(_GET_LONG_FIELD(this, "mObject"));
	char **locales = AssetManager_getLocales(asset_manager, true);
	int i = 0;
	while (locales[i] != NULL) i++;
	jobjectArray array = (*env)->NewObjectArray(env, i, (*env)->FindClass(env, "java/lang/String"), NULL);
	for (i = 0; locales[i] != NULL; i++) {
		(*env)->SetObjectArrayElement(env, array, i, (*env)->NewStringUTF(env, locales[i]));
		free(locales[i]);
	}
	free(locales);
	return array;
}
