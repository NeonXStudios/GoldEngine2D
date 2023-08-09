#include "RightClickUI.h"


void RightClickUI::draw() {


    if (ImGui::IsMouseClicked(1)) {
        MousePosition = ImGui::GetMousePos();
        ImGui::SetNextWindowPos(ImVec2(MousePosition.x, MousePosition.y));
        ImGui::SetNextWindowSize(ImVec2(300, 500));

        miniMenuOpen = true;
    }
    if (miniMenuOpen && ImGui::Begin("Assets Menu", &miniMenuOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
        if (ImGui::BeginMenu("Create")) {
            if (ImGui::Button("New Entity")) {
                SceneManager::GetSceneManager()->NewEntity();
                std::cout << "NEW OBJECT CREATED" << std::endl;
            }
            ImGui::EndMenu();
        }
        ImGui::End();
    }

    if (ImGui::IsMouseReleased (0)) {
        miniMenuOpen = false;
    }
}


void RightClickUI::start(){}

void RightClickUI::update() {}

void RightClickUI::lateupdate() {}

void RightClickUI::fixupdate() {}