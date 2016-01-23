#环境配置
* 参照 引擎目录/tools/to_js/README.mdown

#执行绑定
* 将本目录拷贝至 引擎目录/tools/
* 运行js_bindings.py进行js绑定
* 运行lua_bindings.py进行lua绑定

#常见问题
##lua绑定不支持lambda
将绑定文件中的
do {
	// Lambda binding for lua is not supported.
	assert(false);
} while(0)
修改为
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
需添加头文件#include "CCLuaEngine.h"

##os x 10.11下绑定失败
Exception: can't open libclang.dylib
解决方案：修改 引擎目录/tools/bindings-generator/clang/cindex.py
找到library = cdll.LoadLibrary(self.get_filename())
修改为library = cdll.LoadLibrary('../bindings-generator/libclang/' + self.get_filename())

##lua绑定失败
Exception: The namespace (Evo::TalkWidget) conversion wasn't set in 'ns_map' section of the conversions.yaml
解决方案：修改 引擎目录/tools/bindings-generator/targets/lua/conversions.yaml
将自订的 namespace 加到 ns_map 的变数中
---------------------------------------------------------------------------------------
ns_map:
...
"cocosbuilder::": "cc."
"CocosDenshion::": "cc."
"VCT::": "VCT."
---------------------------------------------------------------------------------------

其他参考资料 ：http://www.cocoachina.com/bbs/read.php?tid=196037