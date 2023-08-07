#pragma once
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "../../source/Graphics/AppSettings.h"

class UIDrawer
{
public:
	virtual void start () = 0;
	virtual void draw  () = 0;
	virtual void update() = 0;
	virtual void lateupdate() = 0;
	virtual void fixupdate() = 0;
};