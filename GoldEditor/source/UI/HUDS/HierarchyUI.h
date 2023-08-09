#pragma once
#include "../UIDrawer.h"
#include "../../../source/EngineBehaviour/GoldEngineLib.h"


class HierarchyUI : public UIDrawer {
public:
    bool SelectInHierarchy;
    void start() override {
        
    }


    void draw() override;

    void update() override {

    }

    void lateupdate() override {

    }


    void fixupdate() override {
    }
};