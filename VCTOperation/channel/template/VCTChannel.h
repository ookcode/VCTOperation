//
//  VCTChannel.h
//  operation
//
//  Created by Vincent on 15-2-2.
//
//

#ifndef __VCTChannel__
#define __VCTChannel__

#define SUPPORT_JS
#define SUPPORT_CPP

#include <functional>
#include <string>
#include <map>

#ifdef SUPPORT_JS
#include "jsapi.h"
#endif

namespace VCT
{
#ifdef SUPPORT_JS
    //js回调函数定义
    typedef jsval JS_CALLBACK;
#endif
    
#ifdef SUPPORT_CPP
    //c++回调函数定义
    typedef std::function<void(const std::string&)> CPP_CALLBACK;
#endif
    
    class Channel
    {
    public:
        //请求通道
        template<typename T>
        static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args, T &callback);
        //回调通道
        static void Response(const std::string& args,const std::string& address);
        
    private:
#ifdef SUPPORT_JS
        //对js回调函数取地址，存储在JS_CALLBACK_MAP中
        static std::string getAddressAndSave(JS_CALLBACK &callback);
        static std::map<std::string, JS_CALLBACK> JS_CALLBACK_MAP;
#endif
        
#ifdef SUPPORT_CPP
        //对c++回调函数取地址，存储在CPP_CALLBACK_MAP中
        static std::string getAddressAndSave(CPP_CALLBACK &callback);
        static std::map<std::string, CPP_CALLBACK> CPP_CALLBACK_MAP;
#endif
    };
}

#endif //__VCTChannel__
