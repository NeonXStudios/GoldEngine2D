#pragma once
#include "../UIDrawer.h"

class RightClickUI : public UIDrawer
{
    ImVec2 MousePos;

public:
    bool miniMenuOpen = false;
    bool SceneHover;
    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
};