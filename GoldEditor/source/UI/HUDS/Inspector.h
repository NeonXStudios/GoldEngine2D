#include "../UIDrawer.h"

class InspectorUI : public UIDrawer {

public:
    void start() override {

    }

    void draw() override {
        ImGui::Begin("Inspector");

        ImGui::End();
    }

    void update() override {

    }

    void lateupdate() override {

    }

    void fixupdate() override {

    }
};