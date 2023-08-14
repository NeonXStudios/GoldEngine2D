#include "RightClickUI.h"


void RightClickUI::draw() {

    if (ImGui::IsMouseClicked(0)) {
        miniMenuOpen = false;
    }

    if (SceneHover && ImGui::IsMouseClicked(1)) {
        MousePos = ImGui::GetMousePos();
        ImGui::SetNextWindowPos(ImVec2(MousePos.x, MousePos.y));
        ImGui::SetNextWindowSize(ImVec2(300, 500));

        miniMenuOpen = true;
    }

    if (SceneHover && miniMenuOpen && ImGui::Begin("Assets Menu", &miniMenuOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
        if (ImGui::BeginMenu("Create")) {
            if (ImGui::Button("New Entity")) {
                SceneManager::GetSceneManager()->NewEntity();
                std::cout << "NEW OBJECT CREATED" << std::endl;
                miniMenuOpen = false;
            }
            ImGui::EndMenu();
        }
        ImGui::End();
    }
}


void RightClickUI::start(){}

void RightClickUI::update() {}

void RightClickUI::lateupdate() {}

void RightClickUI::fixupdate() {}