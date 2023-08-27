#pragma once
#include "../AComponent.h"

class CBoxCollider3D : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner) override;
};
