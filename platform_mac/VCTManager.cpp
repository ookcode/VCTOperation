//
//  VCTManager.cpp
//  PixelsMaker
//
//  Created by Vincent on 15/11/12.
//
//

#include "VCTManager.h"
std::string VCTManager::Request(const std::string& moduleName, const std::string& methodName,const std::string& args, const std::string& cbaddress)
{
    std::string module = moduleName;
    std::transform(module.begin(), module.end(), module.begin(), tolower);
    if (module == "sysmodule")
    {
        std::string method = methodName;
        std::transform(method.begin(), method.end(), method.begin(), tolower);
        if (method == "getbuildversion") return "1.0.0";
        if (method == "getversion") return "1.0.0";
        if (method == "getosversion") return "mac";
        if (method == "getdevice") return "mac";
        if (method == "getudid") return "1111-1111-1111-1111-1111";
    }
    return "";
}