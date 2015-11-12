//
//  VCTCPP2OC.cpp
//  demo
//
//  Created by Vincent on 15/7/17.
//
//

#include "VCTCPP2OC.h"
#import "VCTManager.h"

std::string VCTCPP2OC::Request(const std::string& moduleName, const std::string& methodName,const std::string& args, const std::string& cbaddress)
{
    NSString *module = [NSString stringWithUTF8String:moduleName.c_str()];
    NSString *method = [NSString stringWithUTF8String:methodName.c_str()];
    NSString *param = [NSString stringWithUTF8String:args.c_str()];
    NSString *cb = [NSString stringWithUTF8String:cbaddress.c_str()];
    NSLog(@"**************Request**************");
    NSLog(@"module = %@",module);
    NSLog(@"method = %@",method);
    NSLog(@"param = %@",param);
    NSLog(@"cbaddress = %@",cb);
    NSLog(@"***********************************");
    NSString *returnvalue = [[VCTManager instance] requestWithModuleName:module MethodName:method Param:param Callback:cb];
    return returnvalue.UTF8String;
}