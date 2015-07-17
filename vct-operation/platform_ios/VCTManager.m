//
//  VCTManager.m
//  operation
//
//  Created by Vincent on 15-1-26.
//
//

#import "VCTManager.h"
#import "VCTOC2CPP.h"
@implementation VCTManager
create_impl(VCTManager)

- (id)init {
    if (self = [super init]) {
        moduleDic_ = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)registerModule:(VCTModule *)module {
    if (!module) {
        NSLog(@"register module '%@' fail",module.moduleName);
        return;
    }
    [moduleDic_ setObject:module forKey:module.moduleName];
}

- (NSString *)requestWithModuleName:(NSString *)moduleName
                         MethodName:(NSString *)methodName
                              Param:(NSString *)param
                           Callback:(NSString *)callback {
    
    VCTModule *module = [moduleDic_ objectForKey:moduleName];
    if (!module) {
        NSLog(@"module '%@' not found",moduleName);
        return @"-1";
    }
    NSString *result = [module executeMethodWithName:methodName Param:param Callback:callback];
    return result;
}

- (void)response:(NSString *)param Callback:(NSString *)callback {
    [VCTOC2CPP response:param Callback:callback];
}

@end