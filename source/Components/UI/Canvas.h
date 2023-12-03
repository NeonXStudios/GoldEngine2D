#pragma once
#include "../../source/EngineBehaviour/GoldEngineLib.h"


#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

/// <summary>
/// UI COMPONENTS
/// </summary>
#include "UIBehaviour.h"
#include "ComponentsUI/UIButton.h"


using namespace std;

class Canvas : public Component
{
public:
	std::vector<UIBehaviour*> Data = std::vector<UIBehaviour*>();

	void init() override;
	void update() override;
	void draw() override;
	void clean() override;

	string serialize() override;
	void deserialize(std::string g, std::string path = "") override;
};