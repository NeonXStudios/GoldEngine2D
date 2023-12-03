#include "InputBinder.h"
#include "../../Systems/SystemsEvents.h"


void InputBinder::RegisterFunction (ScriptCompiler* luaParent) {
	luaParent->lua["keyDown"] = [](int keyID) { return InputSystem::InputSystem::GetKey(keyID);  };
	luaParent->lua["keyUp"]	  = [](int keyID) { return InputSystem::InputSystem::GetKeyUp(keyID);  };
}