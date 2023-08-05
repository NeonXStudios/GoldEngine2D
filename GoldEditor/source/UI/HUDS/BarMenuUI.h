#include "../UIDrawer.h"

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

            }

            if (ImGui::MenuItem ("Exit")) {
                StartEngineGraphics::closeWindow();
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