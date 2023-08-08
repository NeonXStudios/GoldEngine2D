#pragma once
#include "../UIDrawer.h"
#include "../../../source/EngineBehaviour/GoldEngineLib.h"


class HierarchyUI : public UIDrawer {
public:
    void start() override {
        
    }


    void draw() override {
        ImGui::Begin("Hierarchy");

        for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
            Entity* object = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
            ImVec2 buttonSize(contentRegionAvailable.x, 20);


            ImGui::PushID (i);
            if (ImGui::Button(object->ObjectName.c_str(), buttonSize)) {
                std::cout << "SELECT OBJECT: " << object->ObjectName << std::endl;
            }
            ImGui::PopID();
        }
        ImGui::End();
    }

    void update() {

    }

    void lateupdate() {

    }


    void fixupdate() {
    }
};