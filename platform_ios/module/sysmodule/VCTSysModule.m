//
//  VCTSysModule.m
//  demo
//
//  Created by Vincent on 15/10/9.
//
//

#import "VCTSysModule.h"
#import "JSONKit.h"
#import <AdSupport/ASIdentifierManager.h>
#import "OpenUDID.h"
#define MODULE_NAME @"sysmodule"

#define IOS7_EVALUATE_URL  @"itms-apps://itunes.apple.com/app/id%@"
#define IOS_EVALUATE_URL   @"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@"

@implementation VCTSysModule

create_impl(VCTSysModule)

- (void)dealloc {
    [super dealloc];
}

- (id)init {
    if (self = [super initWithName:MODULE_NAME]) {
        [self registerMethodWithName:@"getversion" Method:@selector(getVersion:Callback:)];
        [self registerMethodWithName:@"getbuildversion" Method:@selector(getBuildVersion:Callback:)];
        [self registerMethodWithName:@"getosversion" Method:@selector(getOSVersion:Callback:)];
        [self registerMethodWithName:@"getdevice" Method:@selector(getDevice:Callback:)];
        [self registerMethodWithName:@"getudid" Method:@selector(getUDID:Callback:)];
        [self registerMethodWithName:@"copy" Method:@selector(copyToClipboard:Callback:)];
        [self registerMethodWithName:@"parse" Method:@selector(getTextFromClipboard:Callback:)];
        [self registerMethodWithName:@"webpageredirect" Method:@selector(webpageredirect:Callback:)];
        [self registerMethodWithName:@"evaluate" Method:@selector(evaluate:Callback:)];
    }
    return self;
}

//跳转网页
- (NSString *)webpageredirect:(NSString *)param Callback:(NSString *)callback {
    NSURL *url = [NSURL URLWithString:param];
    [[UIApplication sharedApplication] openURL:url];
    return @"";
}

//评价，跳转AppStore
- (NSString *)evaluate:(NSString *)param Callback:(NSString *)callback {
    float systemVersion = [[UIDevice currentDevice].systemVersion floatValue];
    NSString* strUrl = systemVersion >= 7.0f ? IOS7_EVALUATE_URL : IOS_EVALUATE_URL;
    NSString *url = [NSString stringWithFormat:strUrl, param];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
    return @"";
}

//获取版本号
- (NSString *)getVersion:(NSString *)param Callback:(NSString *)callback {
    NSDictionary* infoDict = [[NSBundle mainBundle] infoDictionary];
    NSString* GameVersion = [infoDict objectForKey:@"CFBundleShortVersionString"];
    return GameVersion;
}

//获取build版本号
- (NSString *)getBuildVersion:(NSString *)param Callback:(NSString *)callback {
    NSDictionary* infoDict = [[NSBundle mainBundle] infoDictionary];
    NSString* GameVersion = [infoDict objectForKey:@"CFBundleVersion"];
    return GameVersion;
}

//获取系统版本号
- (NSString *)getOSVersion:(NSString *)param Callback:(NSString *)callback {
    NSString *strSysVersion = [[UIDevice currentDevice] systemVersion];
    return strSysVersion;
}

//获取设备类型
- (NSString *)getDevice:(NSString *)param Callback:(NSString *)callback {
    NSString *strModel = [[UIDevice currentDevice] model];
    return strModel;
}

//获取伪UDID
- (NSString *)getUDID:(NSString *)param Callback:(NSString *)callback {
    /************************************************
     检查用户是否允许广告跟踪
     如果允许，则使用IDFA来标识设备
     如果不允许，则使用OpenUDID来标识设备
     *************************************************/
    BOOL allowIDFA = [[ASIdentifierManager sharedManager] isAdvertisingTrackingEnabled];
    if (allowIDFA) {
        NSString *IDFA =[[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
        return IDFA;
    }else {
        NSString *oudid = [OpenUDID value];
        return oudid;
    }
    return @"";
}

//获取剪贴板文本
- (NSString *)getTextFromClipboard:(NSString *)param Callback:(NSString *)callback {
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    return pasteboard.string;
}

//设置剪贴板文本
- (NSString *)copyToClipboard:(NSString *)param Callback:(NSString *)callback {
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    pasteboard.string = param;
    return @"";
}

@end
