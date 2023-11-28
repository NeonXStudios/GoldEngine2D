#pragma once
#include "../UIDrawer.h"
#include "../../Inspector/DrawComponents.h"

class InspectorUI : public UIDrawer {
public:


    static InspectorUI* instance;
    Entity* ObjectSelectToInspector;
    DrawComponents* drawerComponents;

    bool active;

    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;

    void SelectEntity (Entity* newT);
};