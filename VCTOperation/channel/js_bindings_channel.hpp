#ifndef __js_bindings_channel_h__
#define __js_bindings_channel_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_VCT_Channel_class;
extern JSObject *jsb_VCT_Channel_prototype;
void register_all_js_bindings_channel(JSContext* cx, JS::HandleObject obj);
#endif
