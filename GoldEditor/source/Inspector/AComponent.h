#pragma once
#include "../../../source/EngineBehaviour/GoldEngineLib.h"
#include "../UI/EditorUI/EditorGUI.h"
#include <iostream>

class AComponent
{
public:
	virtual void start() = 0;
	virtual void update(Entity* owner) = 0;
};