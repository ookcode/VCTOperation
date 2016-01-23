//
//  VCTChannel.cpp
//  operation
//
//  Created by Vincent on 15-2-2.
//
//

#include "VCTChannel.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
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
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#include "VCTManager.h"
#endif

namespace VCT
{
    std::map<std::string, CALLBACK> Channel::CALLBACK_MAP;
    
    std::string ExecRequest(const std::string &moduleName, const std::string &methodName, const std::string &args, const std::string &address)
    {
        std::string returnvalue("");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        
        //iOS platform will enter here
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
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        returnvalue = VCTManager::Request(moduleName, methodName, args, address);
#endif
        return returnvalue;
    }


    std::string Channel::Request(const std::string &moduleName, const std::string &methodName, const std::string &args, CALLBACK callback)
    {
        std::string address("");
        //whether the callback is null
        if (nullptr != callback)
        {
            //use the methodName + callback address as the key
            std::ostringstream os;
            os << methodName <<  &callback;
            address = os.str();
            CALLBACK_MAP[address] = callback;

        }
        std::string result = ExecRequest(moduleName, methodName, args, address);
        return result;
    }
    
    void Channel::Response(const std::string& args,const std::string& address)
    {
        auto cpp_iter = CALLBACK_MAP.find(address);
        if (cpp_iter != CALLBACK_MAP.end()) {
            //exec the callback function
            CALLBACK callback = (*cpp_iter).second;
            CALLBACK_MAP.erase(cpp_iter);
            callback(args);
        } else {
            CCASSERT(false, "callback not found");
        }
    }
}
