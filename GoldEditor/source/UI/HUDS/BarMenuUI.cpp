#include "BarMenuUI.h"
#include "../UIManager.h"


    void BarMenuUI::start() {

    }

    void BarMenuUI::draw() {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu ("File")) {
            
            if (ImGui::MenuItem ("Open")) {

            }

            if (ImGui::MenuItem ("Save")) {
                SaveData::saveScene();
            }

            if (ImGui::MenuItem ("Build Game")) {

            }


            if (ImGui::MenuItem ("Exit")) {
                StartEngineGraphics::closeWindow();
            }


            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Assets")) {

            if (ImGui::MenuItem("New Empty Object")) {
                SceneManager::GetSceneManager()->NewEntity();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Build")) {

            if (ImGui::MenuItem("Build -> Window")) {
                GameCompiler::compileWindow();
            }

            if (ImGui::MenuItem("Build -> Linux (NOT WORKING)")) {

            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Settings")) {
            

            if (ImGui::MenuItem("Camera Settings")) {
                UIManager::instance->cameraSettingUI->isOpen = true;
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    void BarMenuUI::update() {

    }

    void BarMenuUI::lateupdate() {

    }

    void BarMenuUI::fixupdate() {

    }