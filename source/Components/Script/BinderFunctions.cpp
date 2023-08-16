#include "BinderFunctions.h"


void BinderFunctions::RegisterFunctions (ScriptCompiler* luaParent) {
	luaParent->lua.set_function("print", [](sol::variadic_args args) {
		for (auto arg : args) {
			std::cout << arg.as <string>() << std::endl;
		}
		std::cout << std::endl;
	});
}