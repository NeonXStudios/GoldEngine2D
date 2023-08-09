#pragma once
#include <iostream>
#include "Components/CAudio.h"
#include "Components/CSprite.h"

class DrawComponents
{
public:
	std::vector<AComponent*> componentsDraw;

	void start();
	void update();

};