#pragma once
#include "../AComponent.h"
#include "../../UI/EditorUI/EditorGUI.h"
#include "../ScriptEditor.h"

class CScript : public AComponent
{
	bool ScriptEditorOpen = false;
	ScriptEditor* editor;

	void start() override;
	void draw(Entity* owner) override;
};