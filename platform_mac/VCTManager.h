//
//  VCTManager.hpp
//  PixelsMaker
//
//  Created by Vincent on 15/11/12.
//
//

#ifndef VCTManager_hpp
#define VCTManager_hpp

#include <iostream>

class VCTManager
{
public:
    static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args, const std::string& cbaddress);
};

#endif /* VCTManager_hpp */
