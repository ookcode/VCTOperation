//
//  VCTModule.m
//  operation
//
//  Created by Vincent on 15-1-27.
//
//

#import "VCTModule.h"

/************************************
    selector容器
 ***********************************/
@interface VCTMethodContainer : NSObject
@property(nonatomic,assign) SEL method;
- (id)initWithMethod:(SEL)method;
@end

@implementation VCTMethodContainer
- (id)initWithMethod:(SEL)method {
    if (self = [super init]) {
        [self setMethod:method];
    }
    return self;
}
@end

@implementation VCTModule

- (id)init {
    NSAssert(false, @"subclasses must use initWithName to init");
    return self;
}

- (id)initWithName:(NSString *)name {
    if (self = [super init]) {
        self.moduleName = name;
        _methodDic = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)registerMethodWithName:(NSString *)methodName Method:(SEL)method {
    VCTMethodContainer *container = [[VCTMethodContainer alloc] initWithMethod:method];
    [self.methodDic setObject:container forKey:methodName];
    [container release];
}

- (NSString *)executeMethodWithName:(NSString *)methodName
                              Param:(NSString *)param
                           Callback:(NSString *)callback {
    VCTMethodContainer *container = [self.methodDic objectForKey:methodName];
    SEL method = container.method;
    if ([self respondsToSelector:method]) {
        NSString *result = [self performSelector:method withObject:param withObject:callback];
        return result;
    }
    return @"-1";
}

@end
