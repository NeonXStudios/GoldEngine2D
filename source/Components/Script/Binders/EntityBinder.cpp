#include "EntityBinder.h"



void EntityBinder::RegisterFunctions(ScriptCompiler* luaParent)
{


	luaParent->lua["self"] = sol::make_object(luaParent->lua.lua_state(), luaParent->entity);
	luaParent->lua.new_usertype<Entity>("Object",
		"name", &Entity::ObjectName,
		"tag", &Entity::ObjectTag
	);
}