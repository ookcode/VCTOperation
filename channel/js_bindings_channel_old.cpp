#ifdef COCOS2D_JAVASCRIPT

#include "js_bindings_channel_old.hpp"
#include "cocos2d_specifics.hpp"

#if (COCOS2D_VERSION < 0x00030500)

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
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

        JSObject *_tmp = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        JS_AddObjectRoot(cx, &pp->obj);
        JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, JS::HandleObject obj, JS::HandleId id, JS::MutableHandleValue vp)
{
    vp.set(BOOLEAN_TO_JSVAL(true));
    return true;    
}
JSClass  *jsb_VCT_Channel_class;
JSObject *jsb_VCT_Channel_prototype;

bool js_js_bindings_channel_old_Channel_Request(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        ok &= jsval_to_std_string(cx, argv[1], &arg1);
        ok &= jsval_to_std_string(cx, argv[2], &arg2);
        jsval arg3 = argv[3];
        JSB_PRECONDITION2(ok, cx, false, "js_js_bindings_channel_old_Channel_Request : Error processing arguments");
        std::string ret = VCT::Channel::Request(arg0, arg1, arg2, arg3);
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        JS_SET_RVAL(cx, vp, jsret);
        return true;
    }
    JS_ReportError(cx, "js_js_bindings_channel_old_Channel_Request : wrong number of arguments");
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

void js_register_js_bindings_channel_old_Channel(JSContext *cx, JSObject *global) {
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
        {"__nativeObj", 0, JSPROP_ENUMERATE | JSPROP_PERMANENT, JSOP_WRAPPER(js_is_native_obj), JSOP_NULLWRAPPER},
        {0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("Request", js_js_bindings_channel_old_Channel_Request, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_VCT_Channel_prototype = JS_InitClass(
        cx, global,
        NULL, // parent proto
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

void register_all_js_bindings_channel_old(JSContext* cx, JSObject* obj) {
    // first, try to get the ns
    JS::RootedValue nsval(cx);
    JS::RootedObject ns(cx);
    JS_GetProperty(cx, obj, "VCT", &nsval);
    if (nsval == JSVAL_VOID) {
        ns = JS_NewObject(cx, NULL, NULL, NULL);
        nsval = OBJECT_TO_JSVAL(ns);
        JS_SetProperty(cx, obj, "VCT", nsval);
    } else {
        JS_ValueToObject(cx, nsval, &ns);
    }
    obj = ns;

    js_register_js_bindings_channel_old_Channel(cx, obj);
}

#endif      //(COCOS2D_VERSION < 0x00030500)

#endif      //COCOS2D_JAVASCRIPT