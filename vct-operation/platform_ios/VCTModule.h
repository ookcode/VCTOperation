//
//  VCTModule.h
//  operation
//
//  Created by Vincent on 15-1-27.
//
//

#import <Foundation/Foundation.h>
#import "VCTUtilityMarco.h"

@interface VCTModule : NSObject
@property(nonatomic,retain) NSString *moduleName;
@property(nonatomic,retain) NSMutableDictionary *methodDic;
- (id)init;
- (id)initWithName:(NSString *)name;
- (void)registerMethodWithName:(NSString *)methodName Method:(SEL)method;
- (NSString *)executeMethodWithName:(NSString *)methodName
                              Param:(NSString *)param
                           Callback:(NSString *)callback;
@end
