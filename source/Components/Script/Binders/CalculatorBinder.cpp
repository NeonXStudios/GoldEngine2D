#include "CalculatorBinder.h"


void CalculatorBinder::RegisterFunctions(ScriptCompiler* luaParent)
{

	luaParent->lua.new_usertype < glm::vec2 >("vector2", sol::constructors<glm::vec2(float, float)>(),
		"x", &glm::vec2::x,
		"y", &glm::vec2::y
	);

	luaParent->lua["vector2"]["new"] = [](float x, float y) {
		return glm::vec2(x, y);
		};


	luaParent->lua.new_usertype < glm::vec3 > ("vector3", sol::constructors<glm::vec3(float, float, float)>(),
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z
		);


	luaParent->lua["vector3"]["new"] = [](float x, float y, float z) {
		return glm::vec3(x, y, z);
	};
	



	luaParent->lua.new_usertype < glm::vec4 >("vector4", sol::constructors<glm::vec4(float, float, float, float)>(),
		"x", &glm::vec4::x,
		"y", &glm::vec4::y,
		"z", &glm::vec4::z,
		"w", &glm::vec4::w
	);


	luaParent->lua["vector4"]["new"] = [](float x, float y, float z, float w) {
		return glm::vec4(x, y, z, w);
	};
}