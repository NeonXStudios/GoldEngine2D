#include "HierarchyUI.h"
#include "../UIManager.h"


void HierarchyUI::draw() {

    ImGui::Begin("Hierarchy");

    for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
        Entity* object = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];
        ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
        ImVec2 buttonSize(contentRegionAvailable.x, 20);


        ImGui::PushID(i);
        if (ImGui::Button(object->ObjectName.c_str(), buttonSize)) {
            UIManager::instance->inspectorui->ObjectSelectToInspector = object;
            std::cout << "SELECT OBJECT: " << object->ObjectName << std::endl;
            SelectInHierarchy = true;
        }
        ImGui::PopID();
    }
    ImGui::End();

}