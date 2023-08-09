#pragma once
#include <iostream>
#include "Components/CAudio.h"
#include "Components/CSprite.h"
#include "ComponentList.h"

class DrawComponents
{
public:
	bool miniMenuOpen = false;
	ImVec2 MousePosition;
	std::vector<AComponent*> componentsDraw;

	void start();
	void update();
	void DrawButtons();
};