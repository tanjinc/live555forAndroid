#include <string.h>
#include <jni.h>
#include <android/log.h>
#include "live/mediaServer/live555MediaServer.h"
//#ifdef __cplusplus
//extern "C" {
//#endif
//#include "live/mediaServer/live555MediaServer.h"
#include "test/test.h"
#include "myRTSPServer.h"
//#ifdef __cplusplus
//}
//#endif

#define TAG "HELLO"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO , TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN , TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR , TAG, __VA_ARGS__)

static const char *classPathName = "com/tanjinc/live555android/NativeMethod";
static bool sServerStart = false;

jstring native_stringFromJNI( JNIEnv* env, jobject thiz )  {
    LOGI("native_stringFromJNI");
    return env->NewStringUTF( "Hello from JNI!!! !");
}

jint native_startRTSPServer(JNIEnv *env, jobject thiz) {
    int ret = 0;
    LOGI("sServerStart %d", sServerStart);
    if (!sServerStart) {
//        ret = startLive555RTSPServer();
        ret = startRTSPServer2();
        if (ret > 0) {
            LOGI("startLive555RTSPServer success");
            sServerStart = true;
        } else {
            LOGI("RTSPServer start fail");
        }
    } else {
        ret = 1;
        LOGI("RTSPServer have started");
    }
    return ret;
}


static JNINativeMethod methods[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void*)native_stringFromJNI},
        {"startRTSPServer", "()I", (void*)native_startRTSPServer},
};

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOGI("JNI_OnLoad begin");
    JNIEnv* env = NULL;
    jclass clazz;
    //获取JNI环境对象
    if( vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("ERROR: GetEnv failed\n");
        return JNI_ERR;
    }
    //注册本地方法.Load 目标类
    clazz = env->FindClass(classPathName);
    if (clazz == NULL){
        LOGE("Native registration unable to find class '%s'", classPathName);
        return JNI_ERR;
    }

    //注册本地native方法
    if(env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        LOGE("ERROR: MediaPlayer native registration failed\n");
           return JNI_ERR;
    }

    /* success -- return valid version number */
    return JNI_VERSION_1_4;
}

void JNI_OnUnload(JavaVM* vm, void* reserved) {
    LOGI("JNI_UnLoad");
    sServerStart = false;
}
