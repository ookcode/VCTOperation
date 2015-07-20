//
//  VCTHandleModule.m
//  demo
//
//  Created by Vincent on 15/7/20.
//
//

#import "VCTHandleModule.h"
#import "VCTManager.h"
#define MODULE_NAME @"handlemodule"

@interface VCTHandleModule()
{
    NSMutableDictionary *callbackDic_;
}
@end

@implementation VCTHandleModule
create_impl(VCTHandleModule)
- (id)init {
    if (self = [super initWithName:MODULE_NAME]) {
        callbackDic_ = [[NSMutableDictionary alloc] init];
        [self registerMethodWithName:@"register" Method:@selector(registerHandle:Callback:)];
        [self registerMethodWithName:@"trigger" Method:@selector(triggerHandle:Callback:)];
    }
    return self;
}

- (NSString *)registerHandle:(NSString *)param Callback:(NSString *)callback {
    NSAssert(callback.length != 0, @"[handlemodule] register must provide a callback");
    [callbackDic_ setObject:callback forKey:param];
    return @"1";
}

- (NSString *)triggerHandle:(NSString *)param Callback:(NSString *)callback {
    NSAssert(callback.length == 0, @"[handlemodule] trigger do not need a callback");
    NSString *registeredCallback = [[callbackDic_ objectForKey:param] retain];
    if (nil == registeredCallback) {
        NSLog(@"[handlemodule] trigger %@ is not register",param);
    }else {
        [callbackDic_ removeObjectForKey:param];
        [[VCTManager instance] response:@"" Callback:registeredCallback];
    }
    return @"1";
}
@end
