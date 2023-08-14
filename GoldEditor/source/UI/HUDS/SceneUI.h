#pragma once
#include "../UIDrawer.h"

class SceneUI : public UIDrawer {
public:
    unsigned int framebuffer;
    unsigned int texture;
    ImVec2 imageSizeSCENE;
    double textureMousePosX = 0;
    double textureMousePosY = 0;
    int textureWidth, textureHeight;
    ImVec2 imagePosition;
    bool isdragging;
    bool ObjectSelect;
    bool LockWithGizmos;

    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
    glm::vec2 RotatePoint(const glm::vec2& point, const glm::vec2& center, float angle);
};