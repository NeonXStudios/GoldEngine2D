#include "CameraBinder.h"

void CameraBinder::RegisterFunctions(ScriptCompiler* luaParent)
{
	luaParent->lua["GameCamera"] = sol::make_object(luaParent->lua.lua_state(), SceneManager::GetSceneManager()->OpenScene->worldCamera);
	luaParent->lua.new_usertype<Camera>("Camera",
		"position", &Camera::cameraPosition
	);
}