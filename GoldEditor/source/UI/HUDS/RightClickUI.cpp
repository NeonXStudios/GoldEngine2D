#include "RightClickUI.h"


void RightClickUI::draw() {
        if (!locked && SceneHover && miniMenuOpen) {
            if (ImGui::Begin("Assets Menu", &miniMenuOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
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

        if (SceneHover && ImGui::IsMouseDown (1)) {
            MousePos = ImGui::GetMousePos();           
            ImGui::SetNextWindowPos(ImVec2(MousePos.x, MousePos.y));
            ImGui::SetNextWindowSize(ImVec2(300, 500));

            miniMenuOpen = true;
        }
    

    if (ImGui::IsMouseReleased (0)) {
        miniMenuOpen = false;
    }
}


void RightClickUI::start(){}

void RightClickUI::update() {}

void RightClickUI::lateupdate() {}

void RightClickUI::fixupdate() {}