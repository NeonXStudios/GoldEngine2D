#pragma once
#include "../../Components/Data/SaveData.h"
#include "../../Editor/GameCompiler.h"
#include "../UIDrawer.h"

class BarMenuUI : public UIDrawer {

public:
    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
};