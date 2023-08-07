#pragma once
#include "../../RequireLibs.h"
#include "../../Graphics/StartEngineGraphics.h"


class InputSystem
{
public:
	static bool GetKey (int key)
	{
		return glfwGetKey(StartEngineGraphics::window, key) == GLFW_PRESS;
	}
};