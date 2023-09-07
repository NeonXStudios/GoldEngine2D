#include "Inspector.h"
#include "../EditorUI/EditorGUI.h"




void InspectorUI::start() {
    drawerComponents = new DrawComponents();

}

void InspectorUI::draw() {

    ImGui::Begin("Inspector");
    if (ObjectSelectToInspector != nullptr) {
        ObjectSelectToInspector->ObjectName = EditorGUI::InputText("Name:", ObjectSelectToInspector->ObjectName);
        ObjectSelectToInspector->ObjectTag = EditorGUI::InputText("Tag:", ObjectSelectToInspector->ObjectTag);

        glm::vec3 newPos = EditorGUI::Vector3("Position:", ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition);
        ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition = glm::vec3 (newPos.x, newPos.y, newPos.z);

        if (ObjectSelectToInspector->parent != nullptr) {
            glm::vec3 newPosLocal = EditorGUI::Vector3("Local Position:", ObjectSelectToInspector->getComponent<SpriteComponent>().LocalPosition);
            ObjectSelectToInspector->getComponent<SpriteComponent>().LocalPosition = glm::vec3(newPosLocal.x, newPosLocal.y, newPosLocal.z);
        }

       // ObjectSelectToInspector->getComponent<SpriteComponent>().Scale = EditorGUI::Vector2("Size", ObjectSelectToInspector->getComponent<SpriteComponent>().Scale);
        //ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale = EditorGUI::Float("Global Scale", ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale);
        //ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle = EditorGUI::Float("Rotation", ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle);
        
        ImGui::PushID("TKio4");

        glm::vec3 newScale = EditorGUI::Vector3("Scale:", glm::vec3(
            ObjectSelectToInspector->getComponent<SpriteComponent>().Scale.x,
            ObjectSelectToInspector->getComponent<SpriteComponent>().Scale.y,
            ObjectSelectToInspector->getComponent<SpriteComponent>().Scale.z
        ));

        ObjectSelectToInspector->getComponent<SpriteComponent>().Scale = glm::vec3(newScale.x, newScale.y, newScale.z);
        ImGui::PopID();


        ImGui::PushID("TKio3");

        glm::vec3 newRot = EditorGUI::Vector3("Rotation:", glm::vec3(
            ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngleX,
            ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngleY,
            ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngleZ
        ));

        ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngleX = (float)newRot.x;
        ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngleY = (float)newRot.y;
        ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngleZ = (float)newRot.z;
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
                    ObjectSelectToInspector->getComponent<SpriteComponent>().VertexPath = convertedPath;



                    std::cout << "Convertido: " << convertedPath << std::endl;
                    ObjectSelectToInspector->getComponent<SpriteComponent>().compileShaders();
                }
            }


            ImGui::EndDragDropTarget();
        }

        /*
        glm::vec3 newPos = EditorGUI::Vector3("Position:", ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition);
        ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition = glm::vec3(newPos.x, newPos.y, ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.z);

        glm::vec2 scaleGet = ObjectSelectToInspector->getComponent<SpriteComponent>().Scale;
        float v[2] = {
            scaleGet.x,
            scaleGet.y,
        };

        ImGui::DragFloat2 (EditorGUI::_labelPrefix("Size").c_str(), v);

        if (ObjectSelectToInspector->getComponent<SpriteComponent>().Scale != glm::vec2(v[0], v[1])) {
            ObjectSelectToInspector->getComponent<SpriteComponent>().Scale = glm::vec2 (v[0], v[1]);

            if (ObjectSelectToInspector->hasComponent<RigidBody>()) {
                ObjectSelectToInspector->getComponent<RigidBody>().UpdateCollisions ();
            }
        }


        float getScaleGlobal = ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale;
        ImGui::DragFloat (EditorGUI::_labelPrefix ("Scale").c_str(), &getScaleGlobal);

        if (ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale != getScaleGlobal) {
            ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale = getScaleGlobal;


            if (ObjectSelectToInspector->hasComponent<RigidBody>()) {
                ObjectSelectToInspector->getComponent<RigidBody>().UpdateCollisions();
            }
        }

        float rotAngle = ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle;

        ImGui::DragFloat(EditorGUI::_labelPrefix("Rotation").c_str(), &rotAngle);

        if (ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle != rotAngle) {
            ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle = rotAngle;

            if (ObjectSelectToInspector->hasComponent<RigidBody>()) {
                ObjectSelectToInspector->getComponent<RigidBody>().UpdateCollisions();
            }
        }
        
        */
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Text("COMPONENTS");
        ImGui::Separator();
        //DRAW COMPONENTS IN THE ENTITY
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