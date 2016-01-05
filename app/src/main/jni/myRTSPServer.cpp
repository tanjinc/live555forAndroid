//
// Created by tanjinc on 15-12-31.
//

#include "myRTSPServer.h"
#include <BasicUsageEnvironment.hh>
#include <stdio.h>
#include <cstddef>
#include <pthread.h>
#define TAG2 "myRTSPServer"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG2, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , TAG2, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO , TAG2, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN , TAG2, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR , TAG2, __VA_ARGS__)

void* taskthread(void *env) {
    ((BasicUsageEnvironment*)env)->taskScheduler().doEventLoop();
}

int startRTSPServer2() {
    const char *fileName = "test.mp4";
    BasicTaskScheduler *scheduler = BasicTaskScheduler::createNew();
    BasicUsageEnvironment *env = BasicUsageEnvironment::createNew(*scheduler);

    //1.创建RTSP服务
    RTSPServer *rtspServer = RTSPServer::createNew(*env, 8554, NULL);
    *env <<"Play streams from this server using the URL: " << rtspServer->rtspURLPrefix() << "<filename>\n";

    //2.创建会话
    ServerMediaSession *sms = ServerMediaSession::createNew(*env, fileName);
    //2.1添加视频子会话
    sms->addSubsession(MPEG4VideoFileServerMediaSubsession::createNew(*env, fileName, false));

    //3.为RTSPServer添加session
    rtspServer->addServerMediaSession(sms);
    pthread_t id;
    int ret = pthread_create(&id, NULL, taskthread, env);
    if(ret) {
        *env << "Create pthread error!\n";
        return -1;
    }
    pthread_join(id, NULL);
    return 1;
}