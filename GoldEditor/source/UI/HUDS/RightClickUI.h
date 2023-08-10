#pragma once
#include "../UIDrawer.h"

class RightClickUI : public UIDrawer
{
    bool miniMenuOpen = false;
    ImVec2 MousePos;

public:
    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
};