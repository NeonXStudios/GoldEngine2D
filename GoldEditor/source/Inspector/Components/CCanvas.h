#pragma once
#include "../../UI/EditorUI/EditorGUI.h"
#include "../../Editor/GoldEditor.h"
#include <iostream>
#include <filesystem>

class CCanvas : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner) override;
};