#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../ECS/ECS.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../SceneManager/SceneManager.h"

using namespace std;

class SpriteComponent : public Component
{
public:
    glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float Scale = 25.0f;
    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    string TexturePath = "assets/sprites/tile_0045.png";
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

    ~SpriteComponent();
};
#endif