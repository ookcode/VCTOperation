//
//  VCTManager.cpp
//  PixelsMaker
//
//  Created by Vincent on 15/11/12.
//
//

#include "VCTManager.h"
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>

std::string VCTManager::Request(const std::string& moduleName, const std::string& methodName,const std::string& args, const std::string& cbaddress)
{
    NSLog(@"**************Request**************");
    NSLog(@"module = %s",moduleName.c_str());
    NSLog(@"method = %s",methodName.c_str());
    NSLog(@"param = %s",args.c_str());
    NSLog(@"cbaddress = %s",cbaddress.c_str());
    NSLog(@"***********************************");
    std::string module = moduleName;
    std::transform(module.begin(), module.end(), module.begin(), tolower);
    if (module == "sysmodule") {
        std::string method = methodName;
        std::transform(method.begin(), method.end(), method.begin(), tolower);
        NSDictionary* infoDict = [[NSBundle mainBundle] infoDictionary];
        if (method == "getbuildversion") {
            NSString* buildversion = [infoDict objectForKey:@"CFBundleVersion"];
            return buildversion.UTF8String;
            
        } else if (method == "getversion") {
            NSString* version = [infoDict objectForKey:@"CFBundleShortVersionString"];
            return version.UTF8String;
            
        } else if (method == "getosversion") {
            NSOperatingSystemVersion version = [[NSProcessInfo processInfo] operatingSystemVersion];
            NSString *systemVersion = [NSString stringWithFormat:@"%ld.%ld.%ld", version.majorVersion, version.minorVersion, version.patchVersion];
            return systemVersion.UTF8String;
            
        } else if (method == "getdevice") {
            return "mac";
            
        } else if (method == "getudid") {
            
            int                 mgmtInfoBase[6];
            char                *msgBuffer = NULL;
            size_t              length;
            unsigned char       macAddress[6];
            struct if_msghdr    *interfaceMsgStruct;
            struct sockaddr_dl  *socketStruct;
            NSString            *errorFlag = NULL;
            
            // Setup the management Information Base (mib)
            mgmtInfoBase[0] = CTL_NET;        // Request network subsystem
            mgmtInfoBase[1] = AF_ROUTE;       // Routing table info
            mgmtInfoBase[2] = 0;
            mgmtInfoBase[3] = AF_LINK;        // Request link layer information
            mgmtInfoBase[4] = NET_RT_IFLIST;  // Request all configured interfaces
            
            // With all configured interfaces requested, get handle index
            if ((mgmtInfoBase[5] = if_nametoindex("en0")) == 0)
                errorFlag = @"if_nametoindex failure";
            else
            {
                // Get the size of the data available (store in len)
                if (sysctl(mgmtInfoBase, 6, NULL, &length, NULL, 0) < 0)
                    errorFlag = @"sysctl mgmtInfoBase failure";
                else
                {
                    // Alloc memory based on above call
                    if ((msgBuffer = (char *)malloc(length)) == NULL)
                        errorFlag = @"buffer allocation failure";
                    else
                    {
                        // Get system information, store in buffer
                        if (sysctl(mgmtInfoBase, 6, msgBuffer, &length, NULL, 0) < 0)
                            errorFlag = @"sysctl msgBuffer failure";
                    }
                }
            }
            
            // Befor going any further...
            if (errorFlag != NULL)
            {
                NSLog(@"Error: %@", errorFlag);
                return errorFlag.UTF8String;
            }
            
            // Map msgbuffer to interface message structure
            interfaceMsgStruct = (struct if_msghdr *) msgBuffer;
            
            // Map to link-level socket structure
            socketStruct = (struct sockaddr_dl *) (interfaceMsgStruct + 1);
            
            // Copy link layer address data in socket structure to an array
            memcpy(&macAddress, socketStruct->sdl_data + socketStruct->sdl_nlen, 6);
            
            // Read from char array into a string object, into traditional Mac address format
            NSString *macAddressString = [NSString stringWithFormat:@"%02X:%02X:%02X:%02X:%02X:%02X",
                                          macAddress[0], macAddress[1], macAddress[2],
                                          macAddress[3], macAddress[4], macAddress[5]];
            
            // Release the buffer memory
            free(msgBuffer);
            
            return macAddressString.UTF8String;
        } else {
            NSLog(@"method = %s not found",methodName.c_str());
        }
    } else {
        NSLog(@"module = %s not found",moduleName.c_str());
    }
    return "";
}