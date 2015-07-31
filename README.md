# VCTOperation
VCTOperation是一个适用于coocs2d-x以及cocos2d-js引擎的游戏运营框架。<br>
本框架可以帮助您在游戏中方便快捷的接入各种第三方SDK以及调用各平台的特有功能。<br>
本框架实现了一个通道，让c++以及javascript可以方便的调用objective-c以及java所编写的模块。<br>
# 框架使用说明
##iOS接入指南
1、将vct-operation目录下的channel以及platform_ios导入工程中<br>
![](https://github.com/ookcode/VCTOperation/raw/master/README/add_to_ios.png)
2、在cocos2d-js中使用，需要注册jsb代码，方法如下
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
3、在cocos2d-cpp中使用
```cpp
//在需要使用的类中
#include "VCTChannel.h"
```
4、注册需要使用的模块<br>
（因本框架可能用于多个项目，每个项目所需要用到的模块并不一样，故在AppController.mm中注册）
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
##Android接入指南
writing
##调用方法
1、在c++中调用
```cpp
//cpp调用原型
VCT::Channel::Request("模块名", "方法名", "参数", 回调函数)
```
```cpp
//回调函数约定，带一个string类型参数
[](const std::string& args) {
    ...
}
```
2、在javascript中调用
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
writing