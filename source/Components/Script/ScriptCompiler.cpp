#include "ScriptCompiler.h"
#include "BinderFunctions.h"
#include "nlohmann/json.hpp"
#include "../SaveSystem/CheckVar.h"


using namespace nlohmann;
using namespace std;
using namespace sol;

void ScriptCompiler::init () {
	std::ifstream scrpt("game/assets/" + pathScript + ".sr");


	if (!scrpt.is_open()) {
		std::cerr << "No se pudo abrir el archivo." << std::endl;
	}



	std::string contenido((std::istreambuf_iterator<char>(scrpt)),
		(std::istreambuf_iterator<char>()));

	scrpt.close();

	std::cout << contenido << std::endl;

	std::string content = contenido;

	BinderFunctions::RegisterFunctions(this);

	int result = luaL_loadstring(lua.lua_state(), content.c_str());

	if (result == LUA_OK) {
		result = lua_pcall(lua.lua_state(), 0, LUA_MULTRET, 0);
	}
	else {
		std::string error = lua_tostring(lua.lua_state(), -1);
		std::cout << "Error on compile lua: " << error << std::endl;
		lua_pop(lua.lua_state(), 1);

		std::cout << "Lua error on compiled " << std::endl;
	}
}

void ScriptCompiler::update(){}
void ScriptCompiler::draw(){}
void ScriptCompiler::clean(){}


std::string ScriptCompiler::serialize() {
	json componentData;
	componentData["scriptpath"] = pathScript;

	return componentData.dump();
}

void ScriptCompiler::deserialize(std::string g) {
	json componentData = json::parse(g);

	if (CheckVar::Has(componentData, "scriptpath"))
		pathScript = componentData["scriptpath"];
}