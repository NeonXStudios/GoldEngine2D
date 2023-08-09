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
    float GlobalScale = 1;
    glm::vec2 Scale = glm::vec2 (25, 25);
    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    string TexturePath = "assets/sprites/tree.png";
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

    ~SpriteComponent();
};
#endif