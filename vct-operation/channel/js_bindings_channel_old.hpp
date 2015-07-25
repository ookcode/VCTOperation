/******************************
 
 if your engine version is less than v3.5
 
 you should use this file in AppDelegate.cpp
 
 step1. #include "js_bindings_channel_old.hpp"
 
 step2. sc->addRegisterCallback(register_all_js_bindings_channel_old);
 
 ******************************/
#ifndef __js_bindings_channel_old_h__
#define __js_bindings_channel_old_h__

#ifdef COCOS2D_JAVASCRIPT

#include "jsapi.h"
#include "jsfriendapi.h"
#include "VCTChannel.h"

#if (COCOS2D_VERSION < 0x00030500)

extern JSClass  *jsb_VCT_Channel_class;
extern JSObject *jsb_VCT_Channel_prototype;
void register_all_js_bindings_channel_old(JSContext* cx, JSObject* obj);

#endif      //(COCOS2D_VERSION < 0x00030500)

#endif      //COCOS2D_JAVASCRIPT

#endif      //__js_bindings_channel_old_h__

