#pragma once
#include "../../../source/EngineBehaviour/GoldEngineLib.h"
#include "../UI/EditorUI/EditorGUI.h"
#include <iostream>

class AComponent
{
public:
	virtual void start() = 0;

	template <typename T> void update(Entity* owner, int id) {
        if (owner->hasComponent<T>()) {
            ImGui::PushID(id);
            if (ImGui::Button("X")) {
                if (std::is_same<T, SpriteComponent>::value) {
                    std::cout << "El componente base no puede ser eliminado" << std::endl;
                }
                else {
                    owner->removeComponent<T>();
                }
            }
            else {
                draw(owner);
                ImGui::Separator();
            }
            ImGui::PopID();
        }

	}


	virtual void draw(Entity* owner) = 0;
};