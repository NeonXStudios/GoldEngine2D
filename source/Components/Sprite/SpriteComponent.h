#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../ECS/ECS.h"
#include "../../RequireLibs.h"
#include "../SceneManager/SceneManager.h"

using namespace std;

class SpriteComponent : public Component
{
public:
    glm::vec3 ObjectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 LocalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float GlobalScale = 1;
    float rotationAngle;
    glm::vec2 Scale = glm::vec2 (25, 25);
    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    string TexturePath = "game/assets/sprites/tile_0025.png";
    unsigned int texture;
    unsigned int VBO, VAO, EBO;

    void init() override {
        start();
    }

    void update() override {
        onupdate();
    }

    void start();
    void onupdate();
    void LoadTexture ();

    void clean() override;

    string serialize() override;
    void deserialize(std::string g, std::string path = "") override;
};
#endif