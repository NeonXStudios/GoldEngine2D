#pragma once
#include "../ScriptCompiler.h"
#include <iostream>
#include "sol/sol.hpp"

class EntityBinder
{
public:
	static void RegisterFunctions(ScriptCompiler* luaParent);
};