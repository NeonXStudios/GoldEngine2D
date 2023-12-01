#pragma once
#include "../UIDrawer.h"
#include "../../source/Components/FileSystem/FileSystem.h"

class InfoAssetUI : public UIDrawer
{
public:
    string assetPath;
    GLuint SelectUIIMG;
    bool openUI;

    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;

    void LoadIMG (string pathIMG);
};