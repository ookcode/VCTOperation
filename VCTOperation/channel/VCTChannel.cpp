//
//  VCTChannel.cpp
//  operation
//
//  Created by Vincent on 15-2-2.
//
//

#include "VCTChannel.h"
#include "cocos2d.h"
using namespace cocos2d;

#include "ScriptingCore.h"
/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "VCTOCAdapter.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
extern"C"
{
    void Java_com_vincent_cocos2dx_VCTChannel_Response(JNIEnv *env, jobject thiz, jstring args,jstring callback)
    {
        std::string param = JniHelper::jstring2string(args);
        std::string cb = JniHelper::jstring2string(callback);
        VCT::Channel::Response(param, cb);
    }
}
#endif
*/
namespace VCT
{
    std::map<std::string, CPP_CALLBACK> Channel::CPP_CALLBACK_MAP;
    std::map<std::string, JS_CALLBACK> Channel::JS_CALLBACK_MAP;
    std::string ExecRequest(const std::string &moduleName, const std::string &methodName, const std::string &args, const std::string &address)
    {
        VCT::Channel::Response("test response", address);
        std::string returnvalue("");
        return returnvalue;
    }

    std::string Channel::Request(const std::string &moduleName, const std::string &methodName, const std::string &args, JS_CALLBACK &callback)
    {
        std::string address("");
        if (JSVAL_IS_OBJECT_IMPL(JSVAL_TO_IMPL(callback)))
        {
            std::ostringstream os;
            os << &callback;
            address = os.str();
            JS_CALLBACK_MAP[address] = callback;
        }
        std::string result = ExecRequest(moduleName, methodName, args, address);
        return result;
    }
    
    std::string Channel::Request(const std::string &moduleName, const std::string &methodName, const std::string &args, CPP_CALLBACK callback)
    {
        std::string address("");
        if (nullptr != callback)
        {
            std::ostringstream os;
            os << &callback;
            address = os.str();
            CPP_CALLBACK_MAP[address] = callback;

        }
        std::string result = ExecRequest(moduleName, methodName, args, address);
        return result;
    }
    
    void Channel::Response(const std::string& args,const std::string& address)
    {
        do
        {
            auto cpp_iter = CPP_CALLBACK_MAP.find(address);
            if (cpp_iter != CPP_CALLBACK_MAP.end())
            {
                CPP_CALLBACK callback = (*cpp_iter).second;
                callback(args);
                CPP_CALLBACK_MAP.erase(cpp_iter);
                break;
            }
            auto js_iter = JS_CALLBACK_MAP.find(address);
            if (js_iter != JS_CALLBACK_MAP.end())
            {
                JS_CALLBACK callback = (*js_iter).second;
                JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
                jsval v[] = {std_string_to_jsval(cx, args)};
                JS::RootedValue jsRet(cx);
                
                ScriptingCore::getInstance()->executeJSFunctionWithThisObj(JS::RootedValue(cx, JSVAL_NULL), JS::RootedValue(cx, callback), JS::HandleValueArray::fromMarkedLocation(2, v), &jsRet);
                JS_CALLBACK_MAP.erase(js_iter);
                break;
            }
            CCASSERT(false, "callback not found");
        } while (0);
    }
}
