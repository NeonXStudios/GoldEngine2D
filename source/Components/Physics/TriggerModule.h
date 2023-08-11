#pragma once
#include "../../source/EngineBehaviour/GoldEngineLib.h"
#include "box2d/box2d.h"
#include <iostream>

using namespace std;

class TriggerModule : public b2ContactListener
{
public:
	void BeginContact (b2Contact* contact);
	void EndContact   (b2Contact* contact);
};