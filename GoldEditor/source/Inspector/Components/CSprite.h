#pragma once
#include "../AComponent.h"

class CSprite : public AComponent
{
public:
	void start() override;
	void update (Entity* owner) override;
};