//
//  VCTManager.m
//  operation
//
//  Created by Vincent on 15-1-26.
//
//

#import "VCTManager.h"
#import "VCTOC2CPP.h"

@interface VCTManager()
@property(nonatomic,retain) NSMutableDictionary *moduleDic;
@end

@implementation VCTManager

create_impl(VCTManager)

- (void)dealloc {
    self.moduleDic = nil;
    [super dealloc];
}

- (id)init {
    if (self = [super init]) {
        self.moduleDic = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)registerModule:(VCTModule *)module {
    if (!module) {
        NSLog(@"register module '%@' fail",module.moduleName);
        return;
    }
    [self.moduleDic setObject:module forKey:module.moduleName];
}

- (NSString *)requestWithModuleName:(NSString *)moduleName
                         MethodName:(NSString *)methodName
                              Param:(NSString *)param
                           Callback:(NSString *)callback {
    
    VCTModule *module = [self.moduleDic objectForKey:moduleName];
    if (!module) {
        NSLog(@"module '%@' not found",moduleName);
        return @"";
    }
    NSString *result = [module executeMethodWithName:methodName Param:param Callback:callback];
    return result;
}

- (void)response:(NSString *)param Callback:(NSString *)callback {
    [VCTOC2CPP response:param Callback:callback];
}

@end