#pragma once
#include "../../EngineBehaviour/GoldEngineLib.h"

struct CastData
{
	Entity* object;
};

class ObjectCaster
{
public:
	bool MouseCast (glm::vec2 coords, CastData* data);

private:
	glm::vec2 RotatePoint(const glm::vec2& point, const glm::vec2& center, float angle);
};