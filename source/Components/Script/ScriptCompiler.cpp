#include "ScriptCompiler.h"

//BINDERS
#include "BinderFunctions.h"
#include "Binders/EntityBinder.h"
#include "Binders/CalculatorBinder.h"
#include "Binders/InputBinder.h"

#include "nlohmann/json.hpp"
#include "../SaveSystem/CheckVar.h"
#include "Libs/GMathf/GMathf.h"
#include "../../Graphics/AppSettings.h"
#include "Binders/CameraBinder.h"


using namespace nlohmann;
using namespace std;
using namespace sol;

void ScriptCompiler::init() {

	if (AppSettings::gameRunning && loadD) {
		CalculatorBinder::RegisterFunctions(this);
		BinderFunctions::RegisterFunctions(this);
		EntityBinder::RegisterFunctions(this);

		InputBinder::RegisterFunction(this);
		CameraBinder::RegisterFunctions(this);

		GMathf::RegisterLib(this);

		std::cout << "=======Iniciando script de la ruta " << pathScript << std::endl;
		
		if (std::filesystem::exists(FileSystem::GetAsset(pathScript))) {
			std::ifstream scrpt(FileSystem::GetAsset(pathScript));


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

		
		if (AppSettings::gameRunning && loadD)
		lua["onStart"]();
	}
}

void ScriptCompiler::update()
{
	if (AppSettings::gameRunning && loadD)
	lua["onTick"]();
}

void ScriptCompiler::draw(){}
void ScriptCompiler::clean(){}

std::string ScriptCompiler::serialize() {
	json componentData;
	componentData["scriptpath"] = pathScript;

	return componentData.dump();
}

void ScriptCompiler::deserialize (std::string g, std::string path) {
	json componentData = json::parse(g);
	
	if (CheckVar::Has(componentData, "scriptpath")) {
		pathScript = (string)componentData["scriptpath"];
		std::cout << "+++++++++SCRIPT PATH TO LOAD: " << FileSystem::GetAsset((string)componentData["scriptpath"]) << std::endl;
		loadD = true;
		init();
	}
}

void ScriptCompiler::ontrigger(Entity* obj) {
	if (AppSettings::gameRunning && loadD)	lua["triggerSlap"](obj);
	
}

void ScriptCompiler::ontriggerexit(Entity* obj) {
	if (AppSettings::gameRunning && loadD)	lua["triggerEnd"](obj);
}