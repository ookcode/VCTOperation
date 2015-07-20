//
//  VCTChannel.h
//  operation
//
//  Created by Vincent on 15-2-2.
//
//

#ifndef __VCTChannel__
#define __VCTChannel__

#include <functional>
#include <string>
#include <map>
#include "jsapi.h"

namespace VCT
{
    //c++ 回调函数
    typedef std::function<void(const std::string&)> CPP_CALLBACK;
    
    //js 回调函数
    typedef jsval JS_CALLBACK;
    
    class Channel
    {
    public:
        
        //c++ 请求通道
        static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args = "", CPP_CALLBACK callback = nullptr);
        
        //js 请求通道
        static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args, JS_CALLBACK &callback);

        //统一执行回调
        static void Response(const std::string& args,const std::string& address);
        
    private:
        
        //储存js回调函数
        static std::map<std::string, JS_CALLBACK> JS_CALLBACK_MAP;
        
        //储存c++回调函数
        static std::map<std::string, CPP_CALLBACK> CPP_CALLBACK_MAP;
    };
}

#endif //__VCTChannel__
