#pragma once
#include "../ScriptCompiler.h"
#include <iostream>
#include "sol/sol.hpp"
#include <glm/glm.hpp>

class EntityBinder
{
public:
	static void RegisterFunctions (ScriptCompiler* luaParent);
};