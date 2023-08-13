#include "../UIDrawer.h"
#include "../../Components/Data/SaveData.h"


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

            }

            if (ImGui::MenuItem("Build -> Linux")) {

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