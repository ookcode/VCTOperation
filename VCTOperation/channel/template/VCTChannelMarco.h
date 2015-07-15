//
//  VCTChannelMarco.h
//  cppdemo
//
//  Created by Vincent on 15-2-4.
//
//
#ifndef _VCTChannelMarco_h
#define _VCTChannelMarco_h
#define SUPPORT_JS

#if defined(SUPPORT_JS)
#include "jsapi.h"
#define     JS_CALLBACK     jsval
#define     CALLBACK_IS_VOID(val) (!JSVAL_IS_OBJECT_IMPL(JSVAL_TO_IMPL(val)))
#endif

#if defined(SUPPORT_LUA)
#endif

#endif  //_VCTChannelMarco_h
