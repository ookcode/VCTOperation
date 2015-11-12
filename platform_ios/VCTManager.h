//
//  VCTManager.h
//  operation
//
//  Created by Vincent on 15-1-26.
//
//

#import "VCTModule.h"

@interface VCTManager : NSObject

create_declare(VCTManager)

- (void)registerModule:(VCTModule *)module;

- (NSString *)requestWithModuleName:(NSString *)moduleName
                         MethodName:(NSString *)methodName
                          Param:(NSString *)param
                       Callback:(NSString *)callback;

- (void)response:(NSString *)param Callback:(NSString *)callback;
@end
