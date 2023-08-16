#pragma once
#include "../ScriptCompiler.h"
#include <iostream>
#include "sol/sol.hpp"
#include <glm/glm.hpp>

#include "../../../Graphics/StartEngineGraphics.h"

class InputBinder
{
public:
    static void RegisterFunction (ScriptCompiler* luaParent);
};