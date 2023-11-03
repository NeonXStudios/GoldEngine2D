#include "Inspector.h"
#include "../EditorUI/EditorGUI.h"
#include "../UIManager.h"
#include "../../Inspector/InspectorComponents.h"
#include "../../Editor/GoldEditor.h"

//PROGRAMAR EL DIBUJADO DE COMPONENTES PARA EL MENU ADD COMPONENT
InspectorComponents* components = new InspectorComponents();


void InspectorUI::start() {
    drawerComponents = new DrawComponents();

}

void InspectorUI::draw() {
    ImGui::Begin("Inspector");
    if (ObjectSelectToInspector != nullptr) {
        ObjectSelectToInspector->ObjectName = EditorGUI::InputText("Name:", ObjectSelectToInspector->ObjectName);
        ObjectSelectToInspector->ObjectTag = EditorGUI::InputText("Tag:", ObjectSelectToInspector->ObjectTag);

        glm::vec3 newPos = EditorGUI::Vector3 ("Position:", ObjectSelectToInspector->transform->Position);
        ObjectSelectToInspector->transform->Position = glm::vec3 (newPos.x, newPos.y, newPos.z);

        if (ObjectSelectToInspector->parent != nullptr) {
            glm::vec3 newPosLocal = EditorGUI::Vector3("Local Position:", ObjectSelectToInspector->transform->LocalPosition);
            ObjectSelectToInspector->transform->LocalPosition = glm::vec3(newPosLocal.x, newPosLocal.y, newPosLocal.z);
        }

        ImGui::PushID("TKio4");

        glm::vec3 newScale = EditorGUI::Vector3("Scale:", glm::vec3(
            ObjectSelectToInspector->transform->Scale.x,
            ObjectSelectToInspector->transform->Scale.y,
            ObjectSelectToInspector->transform->Scale.z
        ));

        ObjectSelectToInspector->transform->Scale = glm::vec3(newScale.x, newScale.y, newScale.z);
        ImGui::PopID();


        ImGui::PushID("TKio3");
        
        glm::vec3 newRot = EditorGUI::Vector3("Rotation:", glm::vec3(
            ObjectSelectToInspector->transform->Rotation.x,
            ObjectSelectToInspector->transform->Rotation.y,
            ObjectSelectToInspector->transform->Rotation.z
        ));
        ObjectSelectToInspector->transform->Rotation = glm::vec3 ((float)newRot.x, (float)newRot.y, (float)newRot.z);
        ImGui::PopID();

        if (InputSystem::InputSystem::GetKey (GLFW_KEY_DELETE) && ObjectSelectToInspector != nullptr) {
            SceneManager::GetSceneManager()->Destroy (ObjectSelectToInspector);
            ObjectSelectToInspector = nullptr;
        }


        ObjectSelectToInspector->getComponent<SpriteComponent>().VertexPath   = EditorGUI::InputText("Vertex Shader:", ObjectSelectToInspector->getComponent<SpriteComponent>().VertexPath);
        
        if (ImGui::BeginDragDropTarget())
        {
            ImGuiDragDropFlags target_flags = 0;
            target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
            target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_PATH", target_flags))
            {
                const char* receivedString = static_cast<const char*>(payload->Data);

                if (ImGui::IsMouseReleased(0)) {
                    std::string convertedPath = AComponent::RemoveDir(receivedString);
                    ObjectSelectToInspector->getComponent<SpriteComponent>().VertexPath = convertedPath;



                    std::cout << "Convertido: " << convertedPath << std::endl;
                    ObjectSelectToInspector->getComponent<SpriteComponent>().compileShaders();
                }
            }


            ImGui::EndDragDropTarget();
        }


        ObjectSelectToInspector->getComponent<SpriteComponent>().FragmentPath = EditorGUI::InputText("Fragment Shader", ObjectSelectToInspector->getComponent<SpriteComponent>().FragmentPath);
        if (ImGui::BeginDragDropTarget())
        {
            ImGuiDragDropFlags target_flags = 0;
            target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
            target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_PATH", target_flags))
            {
                const char* receivedString = static_cast<const char*>(payload->Data);

                if (ImGui::IsMouseReleased(0)) {
                    std::string convertedPath = AComponent::RemoveDir(receivedString);
                    ObjectSelectToInspector->getComponent<SpriteComponent>().FragmentPath = convertedPath;



                    std::cout << "Convertido: " << convertedPath << std::endl;
                    ObjectSelectToInspector->getComponent<SpriteComponent>().compileShaders();
                }
            }


            ImGui::EndDragDropTarget();
        }

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("COMPONENTS");
        ImGui::Separator();

        if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
            components->update(UIManager::instance->inspectorui->ObjectSelectToInspector);
        }
        drawerComponents->update();
    }
    ImGui::End();

}

void InspectorUI::update() {

}

void InspectorUI::lateupdate() {

}

void InspectorUI::fixupdate() {

}

void InspectorUI::SelectEntity(Entity* newT) {
    ObjectSelectToInspector = newT;
}