#pragma once
#include "../UIDrawer.h"
#include "../../../../source/Components/TileMap/TileMapComponent.h"

class TileMapUI : public UIDrawer
{
public:
    TileMapComponent* componentSelect;
    bool isOpen;

    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;

    void ReSetup();
};