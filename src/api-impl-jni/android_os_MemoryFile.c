#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <glib.h>

#include "defines.h"
#include "util.h"
#include "generated_headers/android_os_MemoryFile.h"

#ifndef MFD_CLOEXEC
	#define MFD_CLOEXEC 0x0001U
#endif

/*
 * Storage for fd -> {ptr, length} mapping.
 */
static GHashTable *s_mappings = NULL;

typedef struct {
	void *ptr;
	int length;
} Mapping;

static Mapping *get_mapping(int fd)
{
	return s_mappings ? g_hash_table_lookup(s_mappings, GINT_TO_POINTER(fd)) : NULL;
}

static void store_mapping(int fd, void *ptr, int length)
{
	if (!s_mappings)
		s_mappings = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, free);
	Mapping *m = malloc(sizeof(*m));
	m->ptr = ptr;
	m->length = length;
	g_hash_table_insert(s_mappings, GINT_TO_POINTER(fd), m);
}

static void remove_mapping(int fd)
{
	if (s_mappings)
		g_hash_table_remove(s_mappings, GINT_TO_POINTER(fd));
}

JNIEXPORT jobject JNICALL Java_android_os_MemoryFile_native_1open(JNIEnv *env, jclass this, jstring name, jint length)
{
	const char *cname = name ? (*env)->GetStringUTFChars(env, name, NULL) : "memory-file";
	int fd = memfd_create(cname, MFD_CLOEXEC);
	if (name)
		(*env)->ReleaseStringUTFChars(env, name, cname);
	if (fd < 0) {
		(*env)->ThrowNew(env, handle_cache.io_exception.class, "Failed to create memfd");
		return NULL;
	}
	if (length > 0 && ftruncate(fd, length) < 0) {
		close(fd);
		(*env)->ThrowNew(env, handle_cache.io_exception.class, "Failed to set size");
		return NULL;
	}

	jobject result = (*env)->NewObject(env, handle_cache.file_descriptor.class, handle_cache.file_descriptor.constructor);
	(*env)->CallVoidMethod(env, result, handle_cache.file_descriptor.setInt, fd);

	return result;
}

JNIEXPORT jint JNICALL Java_android_os_MemoryFile_native_1mmap(JNIEnv *env, jclass this, jobject fdObj, jint length, jint mode)
{
	int fd = (*env)->CallIntMethod(env, fdObj, handle_cache.file_descriptor.getInt);

	int prot = 0;
	if (mode & 0x1)
		prot |= PROT_READ;
	if (mode & 0x2)
		prot |= PROT_WRITE;

	void *addr = mmap(NULL, length, prot, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		(*env)->ThrowNew(env, handle_cache.io_exception.class, strerror(errno));
		return 0;
	}

	store_mapping(fd, addr, length);
	return fd;
}

JNIEXPORT void JNICALL Java_android_os_MemoryFile_native_1munmap(JNIEnv *env, jclass this, jint address, jint length)
{
	Mapping *m = get_mapping(address);
	if (m) {
		munmap(m->ptr, length);
		remove_mapping(address);
	}
}

JNIEXPORT void JNICALL Java_android_os_MemoryFile_native_1close(JNIEnv *env, jclass this, jobject fdObj)
{
	int fd = (*env)->CallIntMethod(env, fdObj, handle_cache.file_descriptor.getInt);

	if (fd >= 0)
		close(fd);
}

JNIEXPORT jint JNICALL Java_android_os_MemoryFile_native_1read(JNIEnv *env, jclass this, jobject fdObj, jint address, jbyteArray buffer, jint srcOffset, jint destOffset, jint count, jboolean isUnpinned)
{
	Mapping *m = get_mapping(address);
	if (!m) {
		(*env)->ThrowNew(env, handle_cache.io_exception.class, "Memory file has been purged");
		return 0;
	}
	jbyte *buf = (*env)->GetByteArrayElements(env, buffer, NULL);
	memcpy(buf + destOffset, (jbyte *)m->ptr + srcOffset, count);
	(*env)->ReleaseByteArrayElements(env, buffer, buf, 0);
	return count;
}

JNIEXPORT void JNICALL Java_android_os_MemoryFile_native_1write(JNIEnv *env, jclass this, jobject fdObj, jint address, jbyteArray buffer, jint srcOffset, jint destOffset, jint count, jboolean isUnpinned)
{
	Mapping *m = get_mapping(address);
	if (!m) {
		(*env)->ThrowNew(env, handle_cache.io_exception.class, "Memory file has been purged");
		return;
	}
	jbyte *buf = (*env)->GetByteArrayElements(env, buffer, NULL);
	memcpy((jbyte *)m->ptr + destOffset, buf + srcOffset, count);
	(*env)->ReleaseByteArrayElements(env, buffer, buf, 0);
}

JNIEXPORT void JNICALL Java_android_os_MemoryFile_native_1pin(JNIEnv *env, jclass this, jobject fdObj, jboolean pin)
{
}

JNIEXPORT jint JNICALL Java_android_os_MemoryFile_native_1get_1size(JNIEnv *env, jclass this, jobject fdObj)
{
	int fd = (*env)->CallIntMethod(env, fdObj, handle_cache.file_descriptor.getInt);

	struct stat st;
	if (fstat(fd, &st) < 0) {
		(*env)->ThrowNew(env, handle_cache.io_exception.class, strerror(errno));
		return 0;
	}
	return st.st_size;
}
