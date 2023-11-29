#pragma once
#include "../../UI/UIManager.h"
#include "../AComponent.h"


class CTileMap : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner);
	std::string convertToCustomPath(std::string inputPath);
};