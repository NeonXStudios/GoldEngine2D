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

        ObjectSelectToInspector->getComponent<SpriteComponent>().Scale = EditorGUI::Vector2("Size", ObjectSelectToInspector->getComponent<SpriteComponent>().Scale);
        ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale = EditorGUI::Float("Global Scale", ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale);
        ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle = EditorGUI::Float("Rotation", ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle);


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