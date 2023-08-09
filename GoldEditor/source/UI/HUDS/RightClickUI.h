#pragma once
#include "../UIDrawer.h"

class RightClickUI : public UIDrawer
{
public:
    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
};