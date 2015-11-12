//
//  VCTCPP2OC.h
//  demo
//
//  Created by Vincent on 15/7/17.
//
//  cpp call into oc

#ifndef __demo__VCTCPP2OC__
#define __demo__VCTCPP2OC__

#include "VCTChannel.h"

class VCTCPP2OC
{
public:
    static std::string Request(const std::string& moduleName, const std::string& methodName,const std::string& args, const std::string& cbaddress);
};

#endif /* defined(__demo__VCTCPP2OC__) */
