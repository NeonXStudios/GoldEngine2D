#pragma once
#include "../UIDrawer.h"
#include "../../Inspector/DrawComponents.h"

class CameraSetting : public UIDrawer {

public:

    bool isOpen;

    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
};