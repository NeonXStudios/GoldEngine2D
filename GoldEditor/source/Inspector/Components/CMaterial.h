#pragma once
#include "../AComponent.h"
#include "../../UI/EditorUI/EditorGUI.h"
#include "../ScriptEditor.h"

class CMaterial : public AComponent
{
	void start() override;
	void draw(Entity* owner) override;
};