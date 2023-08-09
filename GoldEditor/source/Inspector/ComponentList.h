#pragma once
#include <iostream>
#include "../../source/EngineBehaviour/GoldEngineLib.h"

using namespace std;

class ComponentList
{
public:


	template <typename T>
	static void createNewComponent(std::string ComponentName, Entity* owner) {
		ImVec2 size = ImGui::GetContentRegionAvail();

		if (ImGui::Button(ComponentName.c_str(), ImVec2 (size.x, 25))) {
			if (!owner->hasComponent<T>()) {
				owner->addComponent<T>();
				std::cout << "New component created" << std::endl;
			}
			else {
				std::cout << "THE COMPONENT ALREADY EXIST" << std::endl;
			}
		}
	}
};