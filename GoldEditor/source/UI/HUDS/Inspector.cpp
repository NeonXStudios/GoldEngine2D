#include "Inspector.h"
#include "../EditorUI/EditorGUI.h"





  void InspectorUI::start() {
      drawerComponents = new DrawComponents();

  }

  void InspectorUI::draw() {

      ImGui::Begin("Inspector");
      if (ObjectSelectToInspector != nullptr) {
          ObjectSelectToInspector->ObjectName = EditorGUI::InputText("Name:", ObjectSelectToInspector->ObjectName);

          glm::vec3 newPos = EditorGUI::Vector3("Position:", ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition);
          ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition = glm::vec3(newPos.x, newPos.y, ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.z);

          ObjectSelectToInspector->getComponent<SpriteComponent>().Scale = EditorGUI::Vector2("Size", ObjectSelectToInspector->getComponent<SpriteComponent>().Scale);
          ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale = EditorGUI::Float("Size", ObjectSelectToInspector->getComponent<SpriteComponent>().GlobalScale);
          ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle = EditorGUI::Float("Rotation", ObjectSelectToInspector->getComponent<SpriteComponent>().rotationAngle);
       
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