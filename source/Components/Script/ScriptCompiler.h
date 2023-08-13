#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../../RequireLibs.h"
#include "../../EngineBehaviour/GoldEngineLib.h"
#include "sol/sol.hpp"

using namespace std;

class ScriptCompiler : public Component
{
public:
	string pathScript = "scripts/PrintExample";
	sol::state lua;

	void init() override;

	void update() override;
	void draw() override;
	void clean() override;

	string serialize() override;
	void deserialize(std::string g) override;
};