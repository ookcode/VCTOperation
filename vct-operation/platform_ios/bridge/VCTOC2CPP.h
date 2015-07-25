//
//  VCTOC2CPP.h
//  demo
//
//  Created by Vincent on 15/7/17.
//
//  oc call into cpp

#import <Foundation/Foundation.h>

@interface VCTOC2CPP : NSObject
+ (void)response:(NSString *)param Callback:(NSString *)callback;
@end
