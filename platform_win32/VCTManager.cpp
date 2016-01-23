//
//  VCTManager.cpp
//  demo
//
//  Created by Vincent on 15/10/9.
//
//

#include "VCTManager.h"
#include <algorithm>
#include <windows.h>
#include <conio.h>
std::string VCTManager::Request(const std::string& moduleName, const std::string& methodName,const std::string& args, const std::string& cbaddress)
{
    printf("**************Request**************\n");
    printf("module = %s\n",moduleName.c_str());
    printf("method = %s\n",methodName.c_str());
    printf("param = %s\n",args.c_str());
    printf("cbaddress = %s\n",cbaddress.c_str());
    printf("***********************************\n");
	std::string module = moduleName;
	std::transform(module.begin(), module.end(), module.begin(), tolower);
	if (module == "sysmodule") {
		std::string method = methodName;
		std::transform(method.begin(), method.end(), method.begin(), tolower);
		if (method == "getbuildversion"){
            return "1.0.0";
        } else if (method == "getversion") {
            return "1.0.0";
        } else if (method == "getosversion") {
            return "win32";
        } else if (method == "getdevice") {
            return "win32";
        } else if (method == "getudid") {
            GUID uuid;
            CoCreateGuid(&uuid);
            // Spit the address out
            char mac_addr[18];
            sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
                    uuid.Data4[2], uuid.Data4[3], uuid.Data4[4],
                    uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
            return mac_addr;
        } else {
            printf("method = %s not found\n",methodName.c_str());
        }
	} else {
        printf("module = %s not found\n",moduleName.c_str());
    }
	return "";
}