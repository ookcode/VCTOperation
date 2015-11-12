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
    NSLog(@"**************Response*************");
    NSLog(@"param = %@",param);
    NSLog(@"callback = %@",callback);
    NSLog(@"***********************************");
    VCT::Channel::Response(param.UTF8String, callback.UTF8String);
}
@end
