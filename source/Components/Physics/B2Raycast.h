#pragma once
#include <box2d/box2d.h>
#include <iostream>
#include <glm/fwd.hpp>

using namespace std;

class B2Raycast : public b2RayCastCallback
{
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;
};