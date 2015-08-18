# VCTOperation

VCTOperation是一个适用于coocs2d-x以及cocos2d-js引擎的游戏运营框架。<br>

本框架可以帮助您在游戏中方便快捷的接入各种第三方SDK以及调用各平台的特有功能。<br>

框架中包含了一些常用的平台功能的封装，以及一些常用第三方sdk封装
# 框架使用说明
##iOS接入指南
1、将vct-operation目录下的channel以及platform_ios导入工程中

![](https://github.com/ookcode/VCTOperation/raw/master/README/add_to_ios.png)

##Android接入指南
1、打开安卓工程，右键工程->Build Path->Link Source...

![](https://github.com/ookcode/VCTOperation/raw/master/README/add_to_android.png)

2、导入本框架中的platform_android中core以及module

![](https://github.com/ookcode/VCTOperation/raw/master/README/add_to_android2.png)

3、修改安卓工程jni目录下的Android.mk文件

（若不是cocos2d-js工程，可以不引入js_bindings_channel.cpp以及js_bindings_channel_old.cpp）

![](https://github.com/ookcode/VCTOperation/raw/master/README/add_to_android3.png)

##调用指南
1、在cocos2d-js中使用，需要注册jsb代码，方法如下
```cpp
//在AppDelegate.cpp文件头部加入
#include "js_bindings_channel.hpp"
//如果您的引擎版本低于v3.5，请替换成
#include "js_bindings_channel_old.hpp"
```
```cpp
//在AppDelegate.cpp的applicationDidFinishLaunching函数中（建议在sc->start前）加入
sc->addRegisterCallback(register_all_js_bindings_channel);
//如果您的引擎版本低于v3.5，请替换成
sc->addRegisterCallback(register_all_js_bindings_channel_old);
```
2、iOS初始化

（因本框架可能用于多个项目，每个项目所需要用到的模块并不一样，故在AppController.mm中初始化）
```objective-c
//在AppController.mm顶部加入
#import "VCTModuleExport.h"
```
```objective-c
//在AppController.mm的didFinishLaunchingWithOptions函数中（建议在run()调用之前）加入
//创建模块管理类
VCTManager *manager = [VCTManager instance];
//创建模块（此处创建一个弹提示框的模块）
VCTAlertModule *alert = [VCTAlertModule instance];
//注册模块到管理类
[manager registerModule:alert];
```
3、Android初始化

（因本框架可能用于多个项目，每个项目所需要用到的模块并不一样，故在src下的AppActivity.java中初始化）

![](https://github.com/ookcode/VCTOperation/raw/master/README/android_init.png)

4、在c++中调用
```cpp
#include "VCTChannel.h"
//cpp调用原型
VCT::Channel::Request("模块名", "方法名", "参数", 回调函数)
```
```cpp
//回调函数约定，带一个string类型参数
[](const std::string& args) {
    ...
}
```
5、在javascript中调用
```javascript
//js调用原型
VCT.Channel.Request("模块名", "方法名", "参数", 回调函数)
```
```javascript
//回调函数约定，带一个string类型参数
function(args) {
    ...
}
```
##自定义模块指南
####iOS自定义模块指南
1、新建objective-c类,继承 VCTModule <br>
2、init时需要调用以下方法，传入模块名
```objective-c
if (self = [super initWithName:@"MODULE_NAME"]) {
    ...
}
return self;
```
3、定义方法时采用以下原型，传入参数和回调函数字符串
```objective-c
//回调函数字符串callback建议在此处存为成员变量
- (NSString *)xxxx:(NSString *)param Callback:(NSString *)callback
```
4、将定义的方法注册进模块，传入方法名和函数选择器
```objective-c
[self registerMethodWithName:@"METHOD_NAME" Method:@selector(xxxx:Callback:)];
```
5、调用回调函数，传入回传参数以及回调函数字符串
```objective-c
[[VCTManager instance] response:@"回传参数" Callback:@"回调函数字符串"];
```
6、更多详细请参考[VCTAlertModule.m](https://github.com/ookcode/VCTOperation/blob/master/vct-operation/platform_ios/module/alertmodule/VCTAlertModule.m)<br>

####Android自定义模块指南
1、新建java类,继承 VCTModule <br>
2、构造函数中调用以下方法，传入模块名
```java
super("MODULE_NAME");
```
3、定义方法时采用以下原型，传入参数和回调函数字符串
```java
//回调函数字符串callback建议在此处存为成员变量
public String xxxx(final String param,final String callback)
```
4、将定义的方法注册进模块，传入调用时的方法名和实际方法名
```java
this.RegisterMethod("METHOD_NAME", "xxxx");
```
5、调用回调函数，传入回传参数以及回调函数字符串
```java
VCTChannel.Response("回传参数", @"回调函数字符串");
```
6、更多详细请参考[VCTAlertModule.java](https://github.com/ookcode/VCTOperation/blob/master/vct-operation/platform_android/module/alertmodule/VCTAlertModule.java)
