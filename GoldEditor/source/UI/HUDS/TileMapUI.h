#pragma once
#include "../UIDrawer.h"

#include "../../../../source/Components/TileMap/TileMapComponent.h"

class TileMapUI : public UIDrawer
{
public:
    TileMapComponent* componentSelect;
    Entity* instanceEntity;
    string TileSelect;
    bool EditionModeActive;
    bool isOpen;

    std::vector<GLuint> Images = std::vector<GLuint>();

    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;

    void ReSetup();

    GLuint LoadTexture(string TexturePath);
};