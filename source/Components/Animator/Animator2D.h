#pragma once
#include "AnimationsStates.h"
#include "../../source/EngineBehaviour/GoldEngineLib.h"


#include <iostream>
#include <thread>
#include <chrono>
#include <vector>


using namespace std;

struct AnimationsStates;

class Animator2D : public Component
{
	SpriteComponent* cp;

public:
	float NextFrameTime = 0.1f;

	std::vector<AnimationsStates*> states = std::vector<AnimationsStates*>();
	int SelectState = 0;

	void init() override;
	void update() override;
	void draw() override;
	void clean() override;

	void NextFrame (float wtT);

	string serialize() override;
	void deserialize(std::string g, std::string path = "") override;

	void AddNewState(string StateName);
};