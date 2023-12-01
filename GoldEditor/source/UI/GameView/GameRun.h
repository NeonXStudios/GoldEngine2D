#pragma once
#include "../../UI/UIDrawer.h"
#include "../../Editor/GoldEditor.h"
#include "../../../../source/EngineBehaviour/GoldEngineLib.h"

class GameRun : public UIDrawer
{
public:
    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
};