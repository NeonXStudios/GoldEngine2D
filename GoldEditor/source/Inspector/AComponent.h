#pragma once
#include "../../../source/EngineBehaviour/GoldEngineLib.h"
#include "../UI/EditorUI/EditorGUI.h"
#include <iostream>

class AComponent
{
public:
	virtual void start() = 0;

	template <typename T> void update(Entity* owner) {
		if (owner->hasComponent <T>()) {
			if (ImGui::Button("X")) {
				owner->removeComponent<T>();
				return;
			}
			else {
				draw(owner);
			}
		}
	}


	virtual void draw (Entity* owner) = 0;
};