#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../../RequireLibs.h"
#include "../../EngineBehaviour/GoldEngineLib.h"
#include "sol/sol.hpp"
#include "../FileSystem/FileSystem.h"
#include "../ShaderCompiler/Shader.h"

using namespace std;

class ScriptCompiler : public Component
{
public:
	string pathScript = "";
	sol::state lua;

	void init() override;

	void update() override;
	void draw() override;
	void clean() override;

	void ontrigger(Entity* obj);
	void ontriggerexit(Entity* obj);

	string serialize() override;
	void deserialize(std::string g, std::string path = "") override;
	bool loadD;
};