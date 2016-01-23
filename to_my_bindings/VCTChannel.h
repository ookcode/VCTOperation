//
//  VCTChannel.h
//  VCTOperator
//
//  Created by Vincent on 16-1-23
//
//

#ifndef __VCTChannel__
#define __VCTChannel__

#include "cocos2d.h"
#include <functional>
#include <string>
#include <map>

namespace VCT
{
    typedef std::function<void(const std::string &)> CALLBACK;
    
    class Channel
    {
    public:
        //request channel
        static std::string Request(const std::string& moduleName, const std::string& methodName, const std::string& args = "", CALLBACK callback = nullptr);
        
        //response channel
        static void Response(const std::string& args, const std::string& address);
        
    private:
        //callback map
        static std::map<std::string, CALLBACK> CALLBACK_MAP;
    };
}

#endif //__VCTChannel__
