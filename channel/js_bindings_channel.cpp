#include "js_bindings_channel.hpp"
#include "cocos2d_specifics.hpp"
#include "VCTChannel.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_VCT_Channel_class;
JSObject *jsb_VCT_Channel_prototype;

bool js_channel_Channel_Request(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_channel_Channel_Request : Error processing arguments");

        std::string ret = VCT::Channel::Request(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 3) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        JSB_PRECONDITION2(ok, cx, false, "js_channel_Channel_Request : Error processing arguments");

        std::string ret = VCT::Channel::Request(arg0, arg1, arg2);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::function<void (const std::basic_string<char> &)> arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        do {
		    if(JS_TypeOfValue(cx, args.get(3)) == JSTYPE_FUNCTION)
		    {
		        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
		        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(3)));
		        auto lambda = [=](const std::basic_string<char> & larg0) -> void {
		            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
		            jsval largv[1];
		            largv[0] = std_string_to_jsval(cx, larg0);
		            JS::RootedValue rval(cx);
		            bool succeed = func->invoke(1, &largv[0], &rval);
		            if (!succeed && JS_IsExceptionPending(cx)) {
		                JS_ReportPendingException(cx);
		            }
		        };
		        arg3 = lambda;
		    }
		    else
		    {
		        arg3 = nullptr;
		    }
		} while(0)
		;
        JSB_PRECONDITION2(ok, cx, false, "js_channel_Channel_Request : Error processing arguments");

        std::string ret = VCT::Channel::Request(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_channel_Channel_Request : wrong number of arguments");
    return false;
}

bool js_channel_Channel_Response(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::string arg1;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_channel_Channel_Response : Error processing arguments");
        VCT::Channel::Response(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_channel_Channel_Response : wrong number of arguments");
    return false;
}


void js_register_channel_Channel(JSContext *cx, JS::HandleObject global) {
    jsb_VCT_Channel_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_VCT_Channel_class->name = "Channel";
    jsb_VCT_Channel_class->addProperty = JS_PropertyStub;
    jsb_VCT_Channel_class->delProperty = JS_DeletePropertyStub;
    jsb_VCT_Channel_class->getProperty = JS_PropertyStub;
    jsb_VCT_Channel_class->setProperty = JS_StrictPropertyStub;
    jsb_VCT_Channel_class->enumerate = JS_EnumerateStub;
    jsb_VCT_Channel_class->resolve = JS_ResolveStub;
    jsb_VCT_Channel_class->convert = JS_ConvertStub;
    jsb_VCT_Channel_class->finalize = jsb_ref_finalize;
    jsb_VCT_Channel_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Request", js_channel_Channel_Request, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("Response", js_channel_Channel_Response, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_VCT_Channel_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_VCT_Channel_class,
        dummy_constructor<VCT::Channel>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    // add the proto and JSClass to the type->js info hash table
    JS::RootedObject proto(cx, jsb_VCT_Channel_prototype);
    jsb_register_class<VCT::Channel>(cx, jsb_VCT_Channel_class, proto, JS::NullPtr());
}

void register_all_channel(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "VCT", &ns);

    js_register_channel_Channel(cx, ns);
}

