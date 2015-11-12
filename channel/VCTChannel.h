//
//  VCTChannel.h
//  operation
//
//  Created by Vincent on 15-2-2.
//
//

#ifndef __VCTChannel__
#define __VCTChannel__

#include "cocos2d.h"
#include <functional>
#include <string>
#include <map>

#ifdef COCOS2D_JAVASCRIPT
#include "jsapi.h"
#endif

//get float cocos2d version. ex. 3.6
#define GET_COCOS2D_VERSION() ((COCOS2D_VERSION>>16&0xFF) + (COCOS2D_VERSION>>8&0xFF)*0.1 + (COCOS2D_VERSION&0xFF)*0.01)

namespace VCT
{
    //c++ callback
    typedef std::function<void(const std::string&)> CPP_CALLBACK;
    
#ifdef COCOS2D_JAVASCRIPT
    //js callback
    typedef jsval JS_CALLBACK;
#endif
    
    class Channel
    {
    public:
        
        //c++ request channel
        static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args = "", CPP_CALLBACK callback = nullptr);
        
#ifdef COCOS2D_JAVASCRIPT
        //js request channel
        static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args, JS_CALLBACK &callback);
#endif
        
        //uniform response channel
        static void Response(const std::string& args,const std::string& address);
        
    private:
        
#ifdef COCOS2D_JAVASCRIPT
        //save js callback
        static std::map<std::string, JS_CALLBACK> JS_CALLBACK_MAP;
#endif
        //save cpp callback
        static std::map<std::string, CPP_CALLBACK> CPP_CALLBACK_MAP;
    };
}

#endif //__VCTChannel__
