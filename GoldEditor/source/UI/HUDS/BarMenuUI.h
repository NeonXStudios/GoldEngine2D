#include "../UIDrawer.h"
#include "../../Components/Data/SaveData.h"
#include "../../Editor/GameCompiler.h"

class BarMenuUI : public UIDrawer {

public:
    void start() override {

    }

    void draw() override {
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

        if (ImGui::BeginMenu("Camera")) {
            if (ImGui::Button("Ortho")) {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->proj = Camera::Projection::Orthographic;
            }

            if (ImGui::Button("Perspective")) {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->proj = Camera::Projection::Perspective;
            }

            if (ImGui::MenuItem("Build -> Linux (NOT WORKING)")) {

            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    void update() override {

    }

    void lateupdate() override {

    }

    void fixupdate() override {

    }
};