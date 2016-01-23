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
	std::string module = moduleName;
	std::transform(module.begin(), module.end(), module.begin(), tolower);
	if (module == "sysmodule")
	{
		std::string method = methodName;
		std::transform(method.begin(), method.end(), method.begin(), tolower);
		if (method == "getbuildversion") return "1.0.0";
		if (method == "getversion") return "1.0.0";
		if (method == "getosversion") return "win32";
		if (method == "getdevice") return "win32";
        if (method == "getudid")
        {
            GUID uuid;
            CoCreateGuid(&uuid);
            // Spit the address out
            char mac_addr[18];
            sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
                    uuid.Data4[2], uuid.Data4[3], uuid.Data4[4],
                    uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);
            return mac_addr;
        }
	}
	return "";
}