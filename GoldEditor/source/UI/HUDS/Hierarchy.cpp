#include "HierarchyUI.h"
#include "../UIManager.h"


//FIX CHILDREN DRAW LIST

void HierarchyUI::draw() {

    ImGui::Begin("Hierarchy");
    string name = "Open Scene -> " + *SceneManager::GetOpenSceneName();
    ImGui::Selectable (name.c_str()); 
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECTSPARENT", target_flags))
        {
            const char* receivedString = static_cast<const char*>(payload->Data);
            std::cout << "String recibido: " << std::stoi(receivedString) << std::endl;

            if (ImGui::IsMouseReleased(0)) {
                Entity* objGet = SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString));
                objGet->parent = nullptr;
            }
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::Separator();


    ImGuiDragDropFlags src_flags = 0;
    src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;
    src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;

        for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
        Entity* object = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];
        ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
        ImVec2 buttonSize(contentRegionAvailable.x, 20);


        ImGui::PushID(i);

        
        if (object->parent == nullptr) {
            if (object->childrens.size() > 0) {
                if (ImGui::ArrowButton("##Right", ImGuiDir_Right)) {
                    //isArrowButtonOpen[i] = !isArrowButtonOpen[i];
                }
                ImGui::SameLine();
            }

            if (ImGui::Selectable(object->ObjectName.c_str())) {
                UIManager::instance->inspectorui->ObjectSelectToInspector = object;
                std::cout << "SELECT OBJECT: " << object->ObjectName << std::endl;
                SelectInHierarchy = true;
            }
        }

        if (object->childrens.size() > 0 && object->parent == nullptr /*&& isArrowButtonOpen[i] == true*/) {
            for (int e = 0; e < object->childrens.size(); e++) {
                ImGui::PushID(e);

                Entity* child = object->childrens[e];

                if (ImGui::Selectable(child->ObjectName.c_str())) {
                    UIManager::instance->inspectorui->ObjectSelectToInspector = child;
                    std::cout << "SELECT OBJECT: " << child->ObjectName << std::endl;
                    SelectInHierarchy = true;
                }
                ImGui::PopID();
            }
        }

        //if (ImGui::TreeNode(object->ObjectName.c_str()))
        //{
        //    for (int e = 0; e < object->childrens.size(); e++) {
        //        ImGui::PushID(e);

        //        Entity* child = object->childrens[e];

        //        if (ImGui::Selectable(child->ObjectName.c_str())) {
        //            UIManager::instance->inspectorui->ObjectSelectToInspector = child;
        //            std::cout << "SELECT OBJECT: " << child->ObjectName << std::endl;
        //            SelectInHierarchy = true;
        //        }
        //        ImGui::PopID();
        //    }
        //    ImGui::TreePop();
        //}

        if (ImGui::BeginDragDropTarget())
        {
            ImGuiDragDropFlags target_flags = 0;
            target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
            target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECTSPARENT", target_flags))
            {
                const char* receivedString = static_cast<const char*>(payload->Data);
                std::cout << "String recibido: " << std::stoi(receivedString) << std::endl;
                std::cout << "EL OBJETO QUE CHOCO ES " << object->ObjectName << std::endl;

                if (ImGui::IsMouseReleased (0)) {
                    int objectIndex = std::stoi(receivedString);

                    SpriteComponent* sprite = &SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString))->getComponent<SpriteComponent>();
                    SpriteComponent* parentSprite = &object->getComponent<SpriteComponent>();

                    //glm::vec3 offset = sprite->ObjectPosition - parentSprite->ObjectPosition;

                    Entity* objGet = SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString));
                    objGet->parent = object;
                    objGet->transform->LocalPosition = vec3(0,0,0);

                    object->addChild (SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString)));
                }
            }
            ImGui::EndDragDropTarget();
        }

        if (ImGui::BeginDragDropSource(src_flags))
        {
            const char* filePathN;
            string t = "File " + object->ObjectName;
            ImGui::Text(t.c_str());

            std::string pathToSend = to_string(object->objectID)/*entry.path().string()*/;
            ImGui::SetDragDropPayload("OBJECTSPARENT", pathToSend.c_str(), pathToSend.size() + 1); // +1 para incluir el carácter nulo
            ImGui::EndDragDropSource();
        }
        ImGui::PopID();
    }
    ImGui::End();
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECTSPARENT", target_flags))
        {
            const char* receivedString = static_cast<const char*>(payload->Data);
            std::cout << "String recibido: " << std::stoi(receivedString) << std::endl;

            if (ImGui::IsMouseReleased(0)) {
                Entity* objGet = SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString));
                objGet->parent = nullptr;
            }
        }
        ImGui::EndDragDropTarget();
    }
}