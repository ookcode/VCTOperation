//
//  VCTOC2CPP.m
//  demo
//
//  Created by Vincent on 15/7/17.
//
//

#import "VCTOC2CPP.h"
#include "VCTChannel.h"
@implementation VCTOC2CPP
+ (void)response:(NSString *)param Callback:(NSString *)callback {
    VCT::Channel::Response(param.UTF8String, callback.UTF8String);
}
@end
