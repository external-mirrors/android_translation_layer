#include <libsecret/secret.h>

#include "../defines.h"

#include "../generated_headers/android_accounts_AccountManager.h"

static const SecretSchema account_schema = {
	"android.accounts.Account",
	SECRET_SCHEMA_NONE,
	{{"type", SECRET_SCHEMA_ATTRIBUTE_STRING},
          {"name", SECRET_SCHEMA_ATTRIBUTE_STRING},
          {"key", SECRET_SCHEMA_ATTRIBUTE_STRING},
          {NULL, 0}}
};

/* returns true on success, otherwise logs the error (e.g. no Secret Service running) */
static gboolean check_error(const char *action, GError *error)
{
	if (!error)
		return TRUE;
	g_printerr("AccountManager: failed to %s account data in the keyring: %s\n", action, error->message);
	g_error_free(error);
	return FALSE;
}

JNIEXPORT jstring JNICALL Java_android_accounts_AccountManager_nativeGet(JNIEnv *env, jclass clazz, jstring type_jstr, jstring name_jstr, jstring key_jstr)
{
	const char *type = (*env)->GetStringUTFChars(env, type_jstr, NULL);
	const char *name = (*env)->GetStringUTFChars(env, name_jstr, NULL);
	const char *key = (*env)->GetStringUTFChars(env, key_jstr, NULL);
	GError *error = NULL;
	gchar *value = secret_password_lookup_sync(&account_schema, NULL, &error, "type", type, "name", name, "key", key, NULL);
	check_error("read", error);
	(*env)->ReleaseStringUTFChars(env, type_jstr, type);
	(*env)->ReleaseStringUTFChars(env, name_jstr, name);
	(*env)->ReleaseStringUTFChars(env, key_jstr, key);

	jstring ret = value ? _JSTRING(value) : NULL;
	secret_password_free(value);
	return ret;
}

JNIEXPORT jboolean JNICALL Java_android_accounts_AccountManager_nativeSet(JNIEnv *env, jclass clazz, jstring type_jstr, jstring name_jstr, jstring key_jstr, jstring value_jstr)
{
	GError *error = NULL;
	const char *type = (*env)->GetStringUTFChars(env, type_jstr, NULL);
	const char *name = (*env)->GetStringUTFChars(env, name_jstr, NULL);
	const char *key = (*env)->GetStringUTFChars(env, key_jstr, NULL);
	if (value_jstr) {
		const char *value = (*env)->GetStringUTFChars(env, value_jstr, NULL);
		gchar *label = g_strdup_printf("Android account %s (%s): %s", name, type, key);
		secret_password_store_sync(&account_schema, SECRET_COLLECTION_DEFAULT, label, value, NULL, &error, "type", type, "name", name, "key", key, NULL);
		g_free(label);
		(*env)->ReleaseStringUTFChars(env, value_jstr, value);
	} else {
		secret_password_clear_sync(&account_schema, NULL, &error, "type", type, "name", name, "key", key, NULL);
	}
	(*env)->ReleaseStringUTFChars(env, type_jstr, type);
	(*env)->ReleaseStringUTFChars(env, name_jstr, name);
	(*env)->ReleaseStringUTFChars(env, key_jstr, key);
	return check_error("store", error);
}

JNIEXPORT jboolean JNICALL Java_android_accounts_AccountManager_nativeRemove(JNIEnv *env, jclass clazz, jstring type_jstr, jstring name_jstr)
{
	const char *type = (*env)->GetStringUTFChars(env, type_jstr, NULL);
	const char *name = (*env)->GetStringUTFChars(env, name_jstr, NULL);
	// clears every entry (password, auth tokens, user data) belonging to the account
	GError *error = NULL;
	gboolean removed = secret_password_clear_sync(&account_schema, NULL, &error, "type", type, "name", name, NULL);
	(*env)->ReleaseStringUTFChars(env, type_jstr, type);
	(*env)->ReleaseStringUTFChars(env, name_jstr, name);
	// secret_password_clear_sync returns FALSE if nothing matched, i.e. the account didn't exist
	return check_error("remove", error) && removed;
}

JNIEXPORT jstring JNICALL Java_android_accounts_AccountManager_nativeListAccounts(JNIEnv *env, jclass clazz)
{
	GString *list = g_string_new(NULL);
	GError *error = NULL;
	GList *items = secret_password_search_sync(&account_schema, SECRET_SEARCH_ALL, NULL, &error, "key", "account", NULL);
	check_error("list", error);
	for (GList *l = items; l; l = l->next) {
		GHashTable *attributes = secret_retrievable_get_attributes(l->data);
		g_string_append_printf(list, "%s\n%s\n", (char *)g_hash_table_lookup(attributes, "type"), (char *)g_hash_table_lookup(attributes, "name"));
		g_hash_table_unref(attributes);
	}
	g_list_free_full(items, g_object_unref);

	jstring ret = _JSTRING(list->str);
	g_string_free(list, TRUE);
	return ret;
}
