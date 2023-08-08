#include "Inspector.h"

    void InspectorUI::start()  {

    }

    void InspectorUI::draw()  {
        if (ObjectSelectToInspector != NULL) {
            ImGui::Begin("Inspector");
            std::cout << "OBJECT WORKING" << std::endl;
            ImGui::End();
        }
        else {

        }
    }

    void InspectorUI::update()  {
        if (active)
            std::cout << "CHANGE OBJECT: " << ObjectSelectToInspector->ObjectName << std::endl;
    }

    void InspectorUI::lateupdate() {

    }

    void InspectorUI::fixupdate() {

    }

    void InspectorUI::SelectEntity(Entity* newT) {
        ObjectSelectToInspector = newT;
        std::cout << "CHANGE OBJECT: " << ObjectSelectToInspector->ObjectName << std::endl;
        active = true;
    }
