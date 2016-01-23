#include "base/ccConfig.h"
#ifndef __channel_h__
#define __channel_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_VCT_Channel_class;
extern JSObject *jsb_VCT_Channel_prototype;

bool js_channel_Channel_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_channel_Channel_finalize(JSContext *cx, JSObject *obj);
void js_register_channel_Channel(JSContext *cx, JS::HandleObject global);
void register_all_channel(JSContext* cx, JS::HandleObject obj);
bool js_channel_Channel_Request(JSContext *cx, uint32_t argc, jsval *vp);
bool js_channel_Channel_Response(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __channel_h__
