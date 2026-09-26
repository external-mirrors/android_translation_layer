#include <sys/resource.h>
#include <time.h>

#include "../generated_headers/android_os_Process.h"

JNIEXPORT jboolean JNICALL Java_android_os_Process_is64Bit(JNIEnv *env, jclass this)
{
#ifdef __LP64__
	return 1;
#else
	return 0;
#endif
}

JNIEXPORT jint JNICALL Java_android_os_Process_getThreadPriority(JNIEnv *env, jclass this, jint tid)
{
	return getpriority(PRIO_PROCESS, tid);
}

JNIEXPORT jlong JNICALL Java_android_os_Process_getElapsedCpuTime(JNIEnv *env, jclass this)
{
	struct timespec now;
	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now) != 0)
		return 0;
	return now.tv_sec * 1000 + now.tv_nsec / 1000000;
}
