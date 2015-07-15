//
//  VCTChannel.cpp
//  operation
//
//  Created by Vincent on 15-2-2.
//
//

#include "VCTChannel.h"
#include "cocos2d.h"

#ifdef SUPPORT_JS
#include "ScriptingCore.h"
#endif

using namespace cocos2d;
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

namespace VCT
{
    std::string Channel::getAddressAndSave(JS_CALLBACK &callback)
    {
        std::string address("");
        if (JSVAL_IS_OBJECT_IMPL(JSVAL_TO_IMPL(callback)))
        {
            std::ostringstream os;
            os << &callback;
            address = os.str();
            JS_CALLBACK_MAP[address] = callback;
        }
        return address;
    }
    
    std::string Channel::getAddressAndSave(CPP_CALLBACK &callback)
    {
        std::string address("");
        if (nullptr != callback)
        {
            std::ostringstream os;
            os << &callback;
            address = os.str();
            CPP_CALLBACK_MAP[address] = callback;
        }
        return address;
    }
    
    template<typename T>
    std::string Channel::Request(const std::string &moduleName, const std::string &methodName, const std::string &args, T &callback)
    {
        std::string address = getAddressAndSave(callback);
        std::string returnvalue("");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //returnvalue = VCTOCAdapter::Request(moduleName, methodName, args, address);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo minfo;
        const char * package = "com/vincent/cocos2dx/VCTChannel";
        const char * param = "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;";
        bool exist = JniHelper::getStaticMethodInfo(minfo, package,"Request",param);
        if (exist) {
            //创建参数
            jstring jmodule = minfo.env->NewStringUTF(moduleName.c_str());
            jstring jmethod = minfo.env->NewStringUTF(methodName.c_str());
            jstring jparam = minfo.env->NewStringUTF(args.c_str());
            jstring jcallback = minfo.env->NewStringUTF(address.c_str());
            //调用java静态函数
            jstring result = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,jmodule,jmethod,jparam,jcallback);
            if (result != NULL) {
                returnvalue = JniHelper::jstring2string(result);
            }
            //释放参数
            minfo.env->DeleteLocalRef(jmodule);
            minfo.env->DeleteLocalRef(jmethod);
            minfo.env->DeleteLocalRef(jparam);
            minfo.env->DeleteLocalRef(jcallback);
        }else {
            //函数不存在
            __android_log_print(ANDROID_LOG_INFO, "JNIMsg", "static method 'Request' not found");
            return "-1";
        }
#endif
        return returnvalue;
    }
    
    //回调通道
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
                //参数
                jsval v[] = {std_string_to_jsval(cx, args)};
                //返回值
                JS::RootedValue jsRet(cx);
                
                ScriptingCore::getInstance()->executeJSFunctionWithThisObj(JS::RootedValue(cx, JSVAL_NULL), JS::RootedValue(cx, callback), JS::HandleValueArray::fromMarkedLocation(2, v), &jsRet);
                JS_CALLBACK_MAP.erase(js_iter);
                break;
            }
            assert("callback not found");
        }while (0);
    }
}
