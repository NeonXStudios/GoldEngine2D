#pragma once
#include "../AComponent.h"


class CSkybox : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner);
	std::string convertToCustomPath(std::string inputPath);
};