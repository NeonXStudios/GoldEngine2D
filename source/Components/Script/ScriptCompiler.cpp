#include "ScriptCompiler.h"

//BINDERS
#include "BinderFunctions.h"
#include "Binders/EntityBinder.h"
#include "Binders/CalculatorBinder.h"


#include "nlohmann/json.hpp"
#include "../SaveSystem/CheckVar.h"
#include "Libs/GMathf/GMathf.h"


using namespace nlohmann;
using namespace std;
using namespace sol;

void ScriptCompiler::init () {
	CalculatorBinder::RegisterFunctions(this);
	BinderFunctions::RegisterFunctions(this);
	EntityBinder::RegisterFunctions(this);

	GMathf::RegisterLib(this);

	std::ifstream scrpt("game/assets/" + pathScript + ".sr");


	if (!scrpt.is_open()) {
		std::cerr << "No se pudo abrir el archivo." << std::endl;
	}



	std::string contenido((std::istreambuf_iterator<char>(scrpt)),
		(std::istreambuf_iterator<char>()));

	scrpt.close();

	std::cout << contenido << std::endl;

	std::string content = contenido;
	int result = luaL_loadstring(lua.lua_state(), content.c_str());

	if (result == LUA_OK) {
		result = lua_pcall(lua.lua_state(), 0, LUA_MULTRET, 0);
		if (result != LUA_OK) {
			std::string error = lua_tostring(lua.lua_state(), -1);
			std::cout << "Error on compile lua: " << error << std::endl;
			//std::cout << "Error: " << error << std::endl;
			lua_pop(lua.lua_state(), 1);
		}
		else {
			std::cout << "Lua compiled " << endl;
		}
	}
	else {
		std::string error = lua_tostring(lua.lua_state(), -1);
		std::cout << "Error on compile lua: " << error << std::endl;
		lua_pop(lua.lua_state(), 1);

		std::cout << "Lua error on compiled " << std::endl;
	}
}

void ScriptCompiler::update()
{
	lua["update"]();
}

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