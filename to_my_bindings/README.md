#如何进行自动绑定
##环境配置
* 参照 [README.mdown](https://github.com/cocos2d/cocos2d-x/blob/v3/tools/tojs/README.mdown)

##执行绑定
* 将本目录拷贝至 tools/ 目录下
* 运行js_bindings.py进行js绑定
* 运行lua_bindings.py进行lua绑定

##常见问题
###lua绑定不支持lambda
将绑定文件中的
```c++
do {
	// Lambda binding for lua is not supported.
	assert(false);
} while(0)
```
修改为
```c++
#include "CCLuaEngine.h"
int callback = toluafix_ref_function(tolua_S,5,0);
do {
    auto lambda = [callback](const std::basic_string<char> & larg0) -> void {
        LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
        stack->pushString(larg0);
        stack->executeFunctionByHandler(callback, 1);
        stack->clean();
        LuaEngine::getInstance()->removeScriptHandler(callback);
    };
    arg3 = lambda;
} while(0)
```
###os x 10.11下绑定失败
```
Exception: can't open libclang.dylib
```
解决方案：修改 [tools/bindings-generator/clang/cindex.py](https://github.com/cocos2d/bindings-generator/blob/v3/clang/cindex.py)<br>
找到library = cdll.LoadLibrary(self.get_filename())<br>
修改为library = cdll.LoadLibrary('../bindings-generator/libclang/' + self.get_filename())
###lua绑定失败
```
Exception: conversion wasn't set in 'ns_map' section of the conversions.yaml
```
解决方案：修改 [tools/bindings-generator/targets/lua/conversions.yaml](https://github.com/cocos2d/bindings-generator/blob/v3/targets/lua/conversions.yaml)<br>
将自订的 namespace 加到 ns_map 的中
```xml
ns_map:
...
"cocosbuilder::": "cc."
"CocosDenshion::": "cc."
"VCT::": "VCT."
```
其他参考资料 ：[http://www.cocoachina.com/bbs/read.php?tid=196037](http://www.cocoachina.com/bbs/read.php?tid=196037)<br>