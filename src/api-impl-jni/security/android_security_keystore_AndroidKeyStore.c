#include <gtk/gtk.h>
#include <libsecret/secret.h>

#include "../generated_headers/android_security_keystore_AndroidKeyStore.h"

extern GtkWindow *window;

JNIEXPORT void JNICALL Java_android_security_keystore_AndroidKeyStore_nativeSetKey(JNIEnv *env, jclass clazz, jstring package_name_jstr, jstring alias_jstr, jbyteArray key_jobj)
{
	const char *package_name = NULL;
	const char *app_id = g_application_get_application_id(G_APPLICATION(gtk_window_get_application(window)));
	if ((app_id == NULL || !strcmp(app_id, "com.example.demo_application")) && package_name_jstr) {
		// fall back to package name
		app_id = package_name = (*env)->GetStringUTFChars(env, package_name_jstr, NULL);
	}
	const char *alias = (*env)->GetStringUTFChars(env, alias_jstr, NULL);
	jbyte *key = (*env)->GetByteArrayElements(env, key_jobj, NULL);
	jsize key_len = (*env)->GetArrayLength(env, key_jobj);

	SecretSchema schema = {
		app_id,
		SECRET_SCHEMA_NONE,
		{{"alias", SECRET_SCHEMA_ATTRIBUTE_STRING},
	          {NULL, 0}}
	};
	SecretValue *value = secret_value_new((gchar *)key, key_len, "encoded");
	secret_password_store_binary_sync(&schema, NULL, alias, value, NULL, NULL, "alias", alias, NULL);
	secret_value_unref(value);

	if (package_name)
		(*env)->ReleaseStringUTFChars(env, package_name_jstr, package_name);
	(*env)->ReleaseStringUTFChars(env, alias_jstr, alias);
	(*env)->ReleaseByteArrayElements(env, key_jobj, key, 0);
}

JNIEXPORT jbyteArray JNICALL Java_android_security_keystore_AndroidKeyStore_nativeGetKey(JNIEnv *env, jclass clazz, jstring package_name_jstr, jstring alias_jstr)
{
	const char *package_name = NULL;
	const char *app_id = g_application_get_application_id(G_APPLICATION(gtk_window_get_application(window)));
	if ((app_id == NULL || !strcmp(app_id, "com.example.demo_application")) && package_name_jstr) {
		// fall back to package name
		app_id = package_name = (*env)->GetStringUTFChars(env, package_name_jstr, NULL);
	}
	const char *alias = (*env)->GetStringUTFChars(env, alias_jstr, NULL);

	SecretSchema schema = {
		app_id,
		SECRET_SCHEMA_NONE,
		{{"alias", SECRET_SCHEMA_ATTRIBUTE_STRING},
	          {NULL, 0}}
	};
	SecretValue *value = secret_password_lookup_binary_sync(&schema, NULL, NULL, "alias", alias, NULL);
	if (package_name)
		(*env)->ReleaseStringUTFChars(env, package_name_jstr, package_name);
	(*env)->ReleaseStringUTFChars(env, alias_jstr, alias);
	if (value) {
		gsize length;
		const gchar *encoded = secret_value_get(value, &length);
		jbyteArray key_jobj = (*env)->NewByteArray(env, length);
		(*env)->SetByteArrayRegion(env, key_jobj, 0, length, (jbyte *)encoded);
		secret_value_unref(value);
		return key_jobj;
	} else {
		return NULL;
	}
}
