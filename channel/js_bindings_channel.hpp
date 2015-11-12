/******************************
 
 if your engine version is v3.5 or higher
 
 the SpiderMonkey version is up to v33
 
 you should use this file in AppDelegate.cpp
 
 step1. #include "js_bindings_channel.hpp"
 
 step2. sc->addRegisterCallback(register_all_js_bindings_channel);
 
 ******************************/

#ifndef __js_bindings_channel_h__
#define __js_bindings_channel_h__

#ifdef COCOS2D_JAVASCRIPT

#include "jsapi.h"
#include "jsfriendapi.h"
#include "VCTChannel.h"

#if (COCOS2D_VERSION >= 0x00030500)

extern JSClass  *jsb_VCT_Channel_class;
extern JSObject *jsb_VCT_Channel_prototype;
void register_all_js_bindings_channel(JSContext* cx, JS::HandleObject obj);

#endif      //(COCOS2D_VERSION >= 0x00030500)

#endif      //COCOS2D_JAVASCRIPT

#endif      //__js_bindings_channel_h__
