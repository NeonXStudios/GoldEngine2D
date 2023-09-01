#pragma once
#include <iostream>
#include <vector>
#include "../UIDrawer.h"
#include <imguizmo/ImGuizmo.h>
#include <glm/glm.hpp>


using namespace std;

class SceneUI : public UIDrawer {
public:
    ImVec2 imageSizeSCENE;
    double textureMousePosX = 0;
    double textureMousePosY = 0;
    int textureWidth, textureHeight;
    ImVec2 imagePosition;
    bool isdragging;
    bool ObjectSelect;
    bool LockWithGizmos;
    std::vector<Entity*> objectsInAABB;
    int SelectIndex = 0;


    unsigned int texture;
    unsigned int framebuffer;       // Framebuffer Object
    unsigned int depthTexture;      // Texture to capture depth
    GLuint colorAndDepthTexture; // Variable para almacenar el ID de la textura combinada de color y profundidad
    GLuint depthRenderbuffer;    // Variable para almacenar el ID del renderbuffer de profundidad

    glm::vec2 WorldPoint;

    bool res;
    float* matrix;
    float* view;
    float* projection;



    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
    glm::vec2 RotatePoint(const glm::vec2& point, const glm::vec2& center, float angle);
};