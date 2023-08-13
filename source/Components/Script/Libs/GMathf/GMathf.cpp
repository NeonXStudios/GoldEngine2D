#include "GMathf.h"
#include "../../../Lib/GoldMath/GoldMathf.h"
#include <sol/sol.hpp>

void GMathf::RegisterLib(ScriptCompiler* luaParent) {
	//REGISTER MATH FUNCTIONS
	luaParent->lua.new_usertype<GMathf>("GMathf");

	//CLAMP
	luaParent->lua["GMathf"]["ClampFloat"] = [](float value, float min, float max) { return  GoldMathf::ClampFloat(value, min, max);  };
}