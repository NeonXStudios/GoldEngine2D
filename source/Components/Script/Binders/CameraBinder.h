#pragma once
#include "../ScriptCompiler.h"
#include <iostream>
#include "sol/sol.hpp"
#include <glm/glm.hpp>
#include "../../SceneManager/SceneManager.h"

class CameraBinder
{
public:
	static void RegisterFunctions(ScriptCompiler* luaParent);
};