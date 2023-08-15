#pragma once
#include "../ScriptCompiler.h"
#include <iostream>
#include "sol/sol.hpp"
#include <glm/glm.hpp>

class CalculatorBinder
{
public:
	static void RegisterFunctions(ScriptCompiler* luaParent);
};

