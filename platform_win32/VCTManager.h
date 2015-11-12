//
//  VCTManager.hpp
//  demo
//
//  Created by Vincent on 15/10/9.
//
//

#ifndef VCTManager_h
#define VCTManager_h

#include <iostream>

class VCTManager
{
public:
    static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args, const std::string& cbaddress);
};

#endif /* VCTManager_h */
