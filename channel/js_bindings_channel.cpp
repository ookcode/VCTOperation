#ifdef COCOS2D_JAVASCRIPT

#include "js_bindings_channel.hpp"
#include "cocos2d_specifics.hpp"

#if (COCOS2D_VERSION >= 0x00030500)

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        AddObjectRoot(cx, &pp->obj);
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

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

bool js_js_bindings_channel_Channel_Request(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        jsval arg3 = args.get(3);
        JSB_PRECONDITION2(ok, cx, false, "js_js_bindings_channel_Channel_Request : Error processing arguments");
        std::string ret = VCT::Channel::Request(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_js_bindings_channel_Channel_Request : wrong number of arguments");
    return false;
}



void js_VCT_Channel_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (Channel)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        VCT::Channel *nobj = static_cast<VCT::Channel *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_js_bindings_channel_Channel(JSContext *cx, JS::HandleObject global) {
    jsb_VCT_Channel_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_VCT_Channel_class->name = "Channel";
    jsb_VCT_Channel_class->addProperty = JS_PropertyStub;
    jsb_VCT_Channel_class->delProperty = JS_DeletePropertyStub;
    jsb_VCT_Channel_class->getProperty = JS_PropertyStub;
    jsb_VCT_Channel_class->setProperty = JS_StrictPropertyStub;
    jsb_VCT_Channel_class->enumerate = JS_EnumerateStub;
    jsb_VCT_Channel_class->resolve = JS_ResolveStub;
    jsb_VCT_Channel_class->convert = JS_ConvertStub;
    jsb_VCT_Channel_class->finalize = js_VCT_Channel_finalize;
    jsb_VCT_Channel_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Request", js_js_bindings_channel_Channel_Request, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_VCT_Channel_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_VCT_Channel_class,
        dummy_constructor<VCT::Channel>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "Channel", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<VCT::Channel> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_VCT_Channel_class;
        p->proto = jsb_VCT_Channel_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_js_bindings_channel(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "VCT", &ns);

    js_register_js_bindings_channel_Channel(cx, ns);
}

#endif      //COCOS2D_JAVASCRIPT

#endif      //(COCOS2D_VERSION >= 0x00030500)

