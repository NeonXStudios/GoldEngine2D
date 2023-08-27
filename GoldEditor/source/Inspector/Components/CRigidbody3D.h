#pragma once
#include "../AComponent.h"

class CRigidbody3D : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner) override;
};