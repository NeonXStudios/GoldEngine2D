#include "HierarchyUI.h"
#include "../UIManager.h"


//FIX CHILDREN DRAW LIST

void HierarchyUI::draw() {

    ImGui::Begin("Hierarchy");
    string name = "Open Scene -> " + *SceneManager::GetOpenSceneName();
    ImGui::Selectable (name.c_str()); 
   /* if (ImGui::BeginDragDropTarget())
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
    }*/

    ImGui::Separator();


    ImGuiDragDropFlags src_flags = 0;
    src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;
    src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;

        for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
        Entity* object = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];
        ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
        ImVec2 buttonSize(contentRegionAvailable.x, 20);


        ImGui::PushID(i);


        if (object->childrens.size() == 0) {
            if (object != nullptr && object->parent == nullptr) {
                if (ImGui::Selectable(object->ObjectName.c_str())) {
                    UIManager::instance->inspectorui->ObjectSelectToInspector = object;
                    std::cout << "SELECT OBJECT: " << object->ObjectName << std::endl;
                    SelectInHierarchy = true;
                }


                if (ImGui::BeginDragDropTarget())
                {
                    ImGuiDragDropFlags target_flags = 0;
                    target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
                    target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECTSPARENT", target_flags))
                    {
                        const char* receivedString = static_cast<const char*>(payload->Data);

                        if (ImGui::IsMouseReleased(0)) {
                            std::cout << "El identificador hijo es " << SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString))->objectID << std::endl;
                            std::cout << "El identificador padre es " << object->objectID << std::endl;

                            int objectIndex = std::stoi(receivedString);

                            //glm::vec3 offset = sprite->ObjectPosition - parentSprite->ObjectPosition;

                            Entity* objGet = SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString));
                            objGet->setParent(object);

                            if (objGet->parent != nullptr) {
                                std::cout << "Parent correctly Setup" << std::endl;
                                std::cout << "Parent Childrens  " << objGet->childrens.size() << object->childrens.size() << std::endl;
                            }

                            std::cout << "Childrens " << object->childrens.size() << std::endl;
                        }
                    }
                    ImGui::EndDragDropTarget();
                }

                if (ImGui::BeginDragDropSource(src_flags))
                {
                    const char* filePathN;
                    string t = "File " + object->ObjectName;
                    ImGui::Text(t.c_str());

                    std::string pathToSend = to_string(object->objectID);
                    ImGui::SetDragDropPayload("OBJECTSPARENT", pathToSend.c_str(), pathToSend.size() + 1); // +1 para incluir el carácter nulo
                    ImGui::EndDragDropSource();
                }
            } 
        }
        else {
            if (ImGui::TreeNode(object->ObjectName.c_str())) {
                UIManager::instance->inspectorui->SelectEntity(object);
                
                for (Entity* d : object->childrens) {
                    if (d->childrens.size() > 0) {
                        if (ImGui::TreeNode(d->ObjectName.c_str())) {
                            UIManager::instance->inspectorui->SelectEntity(d);

                            ImGui::TreePop();
                        }
                    }
                    else {
                        if (ImGui::Selectable(d->ObjectName.c_str())) {
                            UIManager::instance->inspectorui->ObjectSelectToInspector = d;
                            std::cout << "SELECT OBJECT: " << d->ObjectName << std::endl;
                        }
                    }
                }
                ImGui::TreePop();
            }
            if (ImGui::BeginDragDropTarget())
            {
                ImGuiDragDropFlags target_flags = 0;
                target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
                target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("OBJECTSPARENT", target_flags))
                {
                    const char* receivedString = static_cast<const char*>(payload->Data);

                    if (ImGui::IsMouseReleased(0)) {
                        std::cout << "El identificador hijo es " << SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString))->objectID << std::endl;
                        std::cout << "El identificador padre es " << object->objectID << std::endl;

                        int objectIndex = std::stoi(receivedString);

                        //glm::vec3 offset = sprite->ObjectPosition - parentSprite->ObjectPosition;

                        Entity* objGet = SceneManager::GetSceneManager()->GetObjectPerIndex(std::stoi(receivedString));
                        objGet->setParent(object);

                        if (objGet->parent != nullptr) {
                            std::cout << "Parent correctly Setup" << std::endl;
                            std::cout << "Parent Childrens  " << objGet->childrens.size() << object->childrens.size() << std::endl;
                        }

                        std::cout << "Childrens " << object->childrens.size() << std::endl;
                    }
                }
                ImGui::EndDragDropTarget();
            }

            if (ImGui::BeginDragDropSource(src_flags))
            {
                const char* filePathN;
                string t = "File " + object->ObjectName;
                ImGui::Text(t.c_str());

                std::string pathToSend = to_string(object->objectID);
                ImGui::SetDragDropPayload("OBJECTSPARENT", pathToSend.c_str(), pathToSend.size() + 1); // +1 para incluir el carácter nulo
                ImGui::EndDragDropSource();
            }
        }
        ImGui::PopID();
    }
    ImGui::End();


    /*if (ImGui::BeginDragDropTarget())
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
    }*/
}