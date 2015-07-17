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
    //c++ callback function
    typedef std::function<void(const std::string&)> CPP_CALLBACK;
    
    //js callback function
    typedef jsval JS_CALLBACK;
    
    class Channel
    {
    public:
        
        //c++ request channel
        static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args = "", CPP_CALLBACK callback = nullptr);
        
        //js request channel
        static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args, JS_CALLBACK &callback);

        //uniform response channel
        static void Response(const std::string& args,const std::string& address);
        
    private:
        
        //js callback function save in JS_CALLBACK_MAP
        static std::map<std::string, JS_CALLBACK> JS_CALLBACK_MAP;
        
        //c++ callback funcion save in CPP_CALLBACK_MAP
        static std::map<std::string, CPP_CALLBACK> CPP_CALLBACK_MAP;
    };
}

#endif //__VCTChannel__
