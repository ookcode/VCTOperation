//
//  VCTChannel.cpp
//  operation
//
//  Created by Vincent on 15-2-2.
//
//

#include "VCTChannel.h"
USING_NS_CC;

#ifdef COCOS2D_JAVASCRIPT
#include "ScriptingCore.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "VCTCPP2OC.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
extern"C"
{
    //java static function Response will call here
    void Java_com_vincent_cocos2dx_VCTChannel_Response(JNIEnv *env, jobject thiz, jstring args,jstring callback)
    {
        std::string param = JniHelper::jstring2string(args);
        std::string cb = JniHelper::jstring2string(callback);
        VCT::Channel::Response(param, cb);
    }
}
#endif

namespace VCT
{
    std::map<std::string, CPP_CALLBACK> Channel::CPP_CALLBACK_MAP;
    
#ifdef COCOS2D_JAVASCRIPT
    std::map<std::string, JS_CALLBACK> Channel::JS_CALLBACK_MAP;
#endif
    
    std::string ExecRequest(const std::string &moduleName, const std::string &methodName, const std::string &args, const std::string &address)
    {
        std::string returnvalue("");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        
        //iOS or mac os x platform will enter here
        returnvalue = VCTCPP2OC::Request(moduleName, methodName, args, address);
        
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        
        //android platform will enter here
        JniMethodInfo minfo;
        
        //android project package name
        const char * package = "com/vincent/cocos2dx/VCTChannel";
        
        //param and return value
        const char * param = "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;";
        
        //whether the java static function Request exist
        bool exist = JniHelper::getStaticMethodInfo(minfo, package,"Request",param);
        
        if (exist) {
            //create for param
            jstring jmodule = minfo.env->NewStringUTF(moduleName.c_str());
            jstring jmethod = minfo.env->NewStringUTF(methodName.c_str());
            jstring jparam = minfo.env->NewStringUTF(args.c_str());
            jstring jcallback = minfo.env->NewStringUTF(address.c_str());
            //call the static funtion Request into java
            jstring result = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,jmodule,jmethod,jparam,jcallback);
            if (result != NULL) {
                returnvalue = JniHelper::jstring2string(result);
            }
            //free jsstring
            minfo.env->DeleteLocalRef(jmodule);
            minfo.env->DeleteLocalRef(jmethod);
            minfo.env->DeleteLocalRef(jparam);
            minfo.env->DeleteLocalRef(jcallback);
        }else {
            __android_log_print(ANDROID_LOG_INFO, "JNIMsg", "static method 'Request' not found");
            return "0";
        }
#endif
        return returnvalue;
    }
    
#ifdef COCOS2D_JAVASCRIPT
    std::string Channel::Request(const std::string &moduleName, const std::string &methodName, const std::string &args, JS_CALLBACK &callback)
    {
        std::string address("");
        //whether the callback is null
        if (JSVAL_IS_OBJECT_IMPL(JSVAL_TO_IMPL(callback)))
        {
            //use the methodName + callback address as the key
            std::ostringstream os;
            os << methodName << &callback;
            address = os.str();
            JS_CALLBACK_MAP[address] = callback;
        }
        std::string result = ExecRequest(moduleName, methodName, args, address);
        return result;
    }
#endif
    
    std::string Channel::Request(const std::string &moduleName, const std::string &methodName, const std::string &args, CPP_CALLBACK callback)
    {
        std::string address("");
        //whether the callback is null
        if (nullptr != callback)
        {
            //use the methodName + callback address as the key
            std::ostringstream os;
            os << methodName <<  &callback;
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
            //first search in CPP_CALLBACK_MAP
            auto cpp_iter = CPP_CALLBACK_MAP.find(address);
            if (cpp_iter != CPP_CALLBACK_MAP.end())
            {
                //exec the callback function
                CPP_CALLBACK callback = (*cpp_iter).second;
                CPP_CALLBACK_MAP.erase(cpp_iter);
                callback(args);
                break;
            }
#ifdef COCOS2D_JAVASCRIPT
            //search in JS_CALLBACK_MAP
            auto js_iter = JS_CALLBACK_MAP.find(address);
            if (js_iter != JS_CALLBACK_MAP.end())
            {
                //exec the callback function
                JS_CALLBACK callback = (*js_iter).second;
                JS_CALLBACK_MAP.erase(js_iter);
                
                JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
                jsval v[] = {std_string_to_jsval(cx, args)};
#if (COCOS2D_VERSION < 0x00030500)
                jsval jsRet;
                ScriptingCore::getInstance()->executeJSFunctionWithThisObj(JSVAL_NULL, callback, 1,v, &jsRet);
#else
                JS::RootedValue jsRet(cx);
                ScriptingCore::getInstance()->executeJSFunctionWithThisObj(JS::RootedValue(cx, JSVAL_NULL), JS::RootedValue(cx, callback), JS::HandleValueArray::fromMarkedLocation(2, v), &jsRet);
#endif
                break;
            }
#endif
            CCASSERT(false, "callback not found");
        } while (0);
    }
}
