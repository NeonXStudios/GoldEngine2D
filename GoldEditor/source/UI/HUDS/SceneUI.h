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
    bool HoveringSceneUI;
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
    bool RayIntersectsAABB (const glm::vec3& rayOrigin, const glm::vec3& rayDirection, const glm::vec3& aabbMin, const glm::vec3& aabbMax);
    glm::vec3 ScreenToWorldRay(float mouseX, float mouseY, int screenWidth, int screenHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    
    bool TestRayOBBIntersection(
        glm::vec3 ray_origin,        // Ray origin, en espacio mundial
        glm::vec3 ray_direction,     // Dirección del rayo (NO la posición objetivo), en espacio mundial. Debe estar normalizado.
        glm::vec3 aabb_min,          // Coordenadas mínimas X,Y,Z de la malla sin transformar.
        glm::vec3 aabb_max,          // Coordenadas máximas X,Y,Z. A menudo, aabb_min*-1 si la malla está centrada, pero no siempre es el caso.
        glm::mat4 ModelMatrix,       // Transformación aplicada a la malla (que también se aplicará a su caja delimitante)
        float& intersection_distance // Salida: distancia entre ray_origin e intersección con el OBB
    );

    void ScreenPosToWorldRay(
        int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
        int screenWidth, int screenHeight,  // Window size, in pixels
        glm::mat4 ViewMatrix,               // Camera position and orientation
        glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
        glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
        glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
    );

    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;

    glm::vec2 RotatePoint(const glm::vec2& point, const glm::vec2& center, float angle);
};