#pragma once
#include "../AComponent.h"


class CSprite : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner);
	std::string convertToCustomPath (std::string inputPath);
};