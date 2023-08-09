#pragma once
#include "../UIDrawer.h"

class InspectorUI : public UIDrawer {

public:
    static InspectorUI* instance;
    Entity* ObjectSelectToInspector;
    bool active;

    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;

    void SelectEntity (Entity* newT);
};