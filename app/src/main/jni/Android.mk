LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := live555

MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/groupsock/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/groupsock/*.c)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/liveMedia/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/liveMedia/*.c)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/BasicUsageEnvironment/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/BasicUsageEnvironment/*.c)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/UsageEnvironment/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/UsageEnvironment/*.c)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/mediaServer/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/live/mediaServer/*.c)
#$(warning $(MY_CPP_LIST))
LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := \
./live/BasicUsageEnvironment/include \
./live/liveMedia/include \
./live/BasicUsageEnvironment/include \
./live/groupsock/include \
./live/UsageEnvironment/include \
./live/mediaServer

LOCAL_CPPFLAGS += -fexceptions -DXLOCALE_NOT_USED=1 -DNULL=0 -DANDROID -DNO_SSTREAM=1 -UIP_ADD_SOURCE_MEMBERSHIP  -lstdc++
LOCAL_LDLIBS    := -lm -llog
include $(BUILD_SHARED_LIBRARY)

######### === for test =================================
include $(CLEAR_VARS)
LOCAL_MODULE := tanjinc
LOCAL_SRC_FILES := test/test.cpp
LOCAL_C_INCLUDES := \
./live/BasicUsageEnvironment/include \
./live/liveMedia/include \
./live/BasicUsageEnvironment/include \
./live/groupsock/include \
./live/UsageEnvironment/include \
./live/mediaServer
LOCAL_LDLIBS    := -lm -llog
include $(BUILD_SHARED_LIBRARY)
######### === for test =================================



include $(CLEAR_VARS)
LOCAL_MODULE := mytest
LOCAL_SRC_FILES += ./myRTSPServer.cpp
LOCAL_SRC_FILES += ./myMain.cpp

LOCAL_C_INCLUDES := \
./live/BasicUsageEnvironment/include \
./live/liveMedia/include \
./live/BasicUsageEnvironment/include \
./live/groupsock/include \
./live/UsageEnvironment/include \
./live/mediaServer
LOCAL_LDLIBS    := -lm -llog
LOCAL_SHARED_LIBRARIES  +=  live555
LOCAL_SHARED_LIBRARIES  +=  tanjinc
include $(BUILD_SHARED_LIBRARY)
