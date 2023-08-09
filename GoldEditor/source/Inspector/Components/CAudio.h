#pragma once
#include "../AComponent.h"

class CAudio : public AComponent
{
public:
	void start  () override;
	void update (Entity* owner) override;
};