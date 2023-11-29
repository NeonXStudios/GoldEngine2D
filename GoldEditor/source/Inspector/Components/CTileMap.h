#pragma once
#include "../../UI/UIManager.h"
#include "../AComponent.h"
#include <iostream>

using namespace std;

class CTileMap : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner);
	std::string convertToCustomPath(std::string inputPath);
};