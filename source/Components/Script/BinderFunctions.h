#pragma once
#include "ScriptCompiler.h"
#include <iostream>
#include "sol/sol.hpp"

using namespace std;
using namespace sol;


class BinderFunctions
{
public:
	static void RegisterFunctions (ScriptCompiler* luaParent);
};