#pragma once
#include "../../Gizmos/GDGizmos.h"
#include "../AComponent.h"

class CAnimator : public AComponent
{
public:
	void start() override;
	void draw(Entity* owner) override;

	CAnimator();
};