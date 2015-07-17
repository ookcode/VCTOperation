LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_SRC_FILES := hellojavascript/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../../vct-operation/channel/VCTChannel.cpp \
				   ../../../vct-operation/channel/js_bindings_channel.cpp \
				   ../../Classes/GameBaseScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../vct-operation/channel

LOCAL_STATIC_LIBRARIES := cocos_jsb_static

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)


$(call import-module,bindings)
