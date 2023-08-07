#pragma once
#include "imgui.h"
#include "../../source/RequireLibs.h"
#include "../../source/Components/Systems/SystemsEvents.h"

class UIDrawer
{
public:
	virtual void start () = 0;
	virtual void draw  () = 0;
	virtual void update() = 0;
	virtual void lateupdate() = 0;
	virtual void fixupdate() = 0;
};