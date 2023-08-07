#pragma once
#include "../ECS/ECS.h"
#include "../../RequireLibs.h"
#include "../SceneManager/SceneManager.h"



using namespace std;

class DrawBox
{
public:
    glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float Scale = 25.0f;
    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    string TexturePath = "assets/sprites/tree.png";
    unsigned int texture;
    unsigned int VBO, VAO, EBO;

    void start();
    void draw();


    //RELEASE
    ~DrawBox();
};