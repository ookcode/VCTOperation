# VCTOperation

VCTOperation是一个适用于coocs2d-x/js/lua引擎的游戏运营框架。<br>

本框架封装了统计调用以及回调接口，能够让你快速从c++/js/lua端调入iOS及android<br>

框架中包含了一些常用的平台功能的封装，以及一些常用第三方sdk封装
# 导入框架
1、iOS工程中：将仓库目录下的channel以及platform_ios导入工程中

2、android工程中：导入仓库目录下的platform_android工程，并关联至android工程中

3、修改android工程jni目录下的Android.mk文件
```mk
LOCAL_SRC_FILES += VCTChannel.cpp文件路径
LOCAL_SRC_FILES += js_bindings_channel.cpp文件路径 #若是js工程
LOCAL_SRC_FILES += lua_bindings_channel.cpp文件路径 #若是lua工程
LOCAL_C_INCLUDES += channel目录路径
```

4、在cocos2d-js中使用，需要注册jsb代码，方法如下
```cpp
//在AppDelegate.cpp文件头部加入
#include "js_bindings_channel.hpp"

//在AppDelegate.cpp的applicationDidFinishLaunching函数中（在sc->start前）加入
sc->addRegisterCallback(register_all_channel);
```

5、在cocos2d-lua中使用，需注册lua绑定代码，方法如下
```cpp
//在AppDelegate.cpp文件头部加入
#include "lua_bindings_channel.hpp"

//在AppDelegate.cpp的applicationDidFinishLaunching函数中（在runtimeEngine->start前）加入
register_all_channel(stack->getLuaState());
```
# 使用说明
1、iOS注册模块
```objective-c
//在AppController.mm顶部加入
#import "VCTModuleExport.h"

//在AppController.mm的didFinishLaunchingWithOptions函数中调用
VCTManager *manager = [VCTManager instance];//创建模块管理类
VCTAlertModule *alert = [VCTAlertModule instance];//创建模块（此处创建一个弹提示框的模块）
[manager registerModule:alert];//注册模块到管理类
```
自定义模块请参考[VCTAlertModule.m](https://github.com/ookcode/VCTOperation/blob/master/platform_ios/module/alertmodule/VCTAlertModule.m)<br>

2、Android注册模块
```java
//在AppActivity.java顶部加入
import com.vincent.cocos2dx.VCTChannel;

//在AppActivity.java的onCreate函数中调用
VCTManager manager = VCTManager.getInstance();//创建模块管理类
VCTAlertModule alert = VCTAlertModule.getInstance(this);//创建模块（此处创建一个弹提示框的模块）
manager.RegisterModule(alert);//注册模块到管理类
```
自定义模块请参考[VCTAlertModule.java](https://github.com/ookcode/VCTOperation/blob/master/platform_android/src/module/alertmodule/VCTAlertModule.java)<br>

3、在c++中调用
```cpp
#include "VCTChannel.h"
//cpp调用原型
VCT::Channel::Request("模块名", "方法名", "参数", 回调函数)
//回调函数约定，带一个string类型参数
[](const std::string& args) {
    ...
}
```
4、在javascript中调用
```javascript
//js调用原型
VCT.Channel.Request("模块名", "方法名", "参数", 回调函数)
//回调函数约定，带一个string类型参数
function(args) {
    ...
}
```

5、在lua中调用
```lua
-- lua调用原型
VCT.Channel:Request("模块名", "方法名", "参数", 回调函数)
-- 回调函数约定，带一个string类型参数
function(args) {
    ...
}
```
# 框架简明架构
![](https://github.com/ookcode/VCTOperation/raw/master/README/简明架构图.png)

