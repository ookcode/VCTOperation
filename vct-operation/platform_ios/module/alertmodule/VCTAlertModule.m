//
//  VCTAlertModule.m
//  operation
//
//  Created by Vincent on 15-1-28.
//
//

#import "VCTAlertModule.h"
#import "VCTManager.h"
#import "JSONKit.h"
#define MODULE_NAME @"alertmodule"

@interface VCTAlertModule()<UIAlertViewDelegate>
@property(nonatomic,retain) NSString *showAlertCB;
@end

@implementation VCTAlertModule

create_impl(VCTAlertModule)

- (id)init {
    if (self = [super initWithName:MODULE_NAME]) {
        [self registerMethodWithName:@"show" Method:@selector(showAlert:Callback:)];
    }
    return self;
}

/*****************************************************************
param:
 {"title":string,"message":string,"leftbtn":string,"rightbtn":string}
callback:
 {"index":int}
 0 leftbtn clicked
 1 rightbtn clicked
******************************************************************/
- (NSString *)showAlert:(NSString *)param Callback:(NSString *)callback {
    NSDictionary *paramDic = [param objectFromJSONString];
    self.showAlertCB = callback;
    NSString *left = [paramDic objectForKey:@"leftbtn"];
    NSString *right = [paramDic objectForKey:@"rightbtn"];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[paramDic objectForKey:@"title"]
                                                    message:[paramDic objectForKey:@"message"]
                                                   delegate:self
                                          cancelButtonTitle:left
                                          otherButtonTitles:right, nil];
    if (left != nil || right != nil)
    {
        [alert show];
    }
    
    [alert release];
    return @"";
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (self.showAlertCB.length == 0) {
        return;
    }
    NSDictionary *resp = [NSDictionary dictionaryWithObject:[NSNumber numberWithInteger:buttonIndex] forKey:@"index"];
    [[VCTManager instance] response:resp.JSONString Callback:self.showAlertCB];
}
@end
