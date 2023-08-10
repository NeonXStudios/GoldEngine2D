#pragma once
#include "../AComponent.h"


class CRigidBody : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner) override;
};