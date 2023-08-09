#include "Inspector.h"
#include "../EditorUI/EditorGUI.h"





  void InspectorUI::start() {

  }

  void InspectorUI::draw() {

      ImGui::Begin("Inspector");
      if (ObjectSelectToInspector != nullptr) {
          ObjectSelectToInspector->ObjectName = EditorGUI::InputText("Name:", &ObjectSelectToInspector->ObjectName);

          glm::vec3 newPos = EditorGUI::Vector3("Position:", ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition);
          ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition = glm::vec3(newPos.x, newPos.y, ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.z);

          ObjectSelectToInspector->getComponent<SpriteComponent>().Scale = EditorGUI::Vector2("Size", ObjectSelectToInspector->getComponent<SpriteComponent>().Scale);
          ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale = EditorGUI::Float("Size", ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale);
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