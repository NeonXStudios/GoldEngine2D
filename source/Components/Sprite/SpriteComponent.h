#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../ECS/ECS.h"
#include "../../RequireLibs.h"
#include "../SceneManager/SceneManager.h"
#include <glm/gtc/quaternion.hpp>

#define LOADMODELCLASS_H
#include "../Models/Model.h"

using namespace std;

class SpriteComponent : public Component
{

public:
    Shader* ourShader = nullptr;
    GLD::Model* ourmodel = nullptr;


    glm::vec3 Min();
    glm::vec3 Max();

    glm::vec3 m_Min;
    glm::vec3 m_Max;

    //glm::vec3 ObjectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    //glm::vec3 LocalPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    //glm::quat rotation;
    //float rotationAngleY, rotationAngleZ, rotationAngleX;

    //float GlobalScale = 1;
    float rotationAngle;
    glm::vec3 Scale = glm::vec3 (1, 1, 1);
    GLuint shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    string TexturePath = "sprites/tile_0115.png";
    string TextureSpecularPath = "Textures/Roughness.png";
    string VertexPath = "shaders/vert.glsl";
    string FragmentPath = "shaders/frag.glsl";


    const char* vertexSh;
    const char* fragSh;

    unsigned int texture;
    unsigned int textureSpecular;
    unsigned int VBO, VAO, EBO;
    glm::mat4 model = glm::mat4(1.0f);

    void init() override {
        start();
    }

    void update() override {
        onupdate();
    }

    void draw() override;
    void PreRender() override;
    void PostRender() override;

    void start();
    void onupdate();
    void LoadTexture ();
    void compileShaders();

    void clean() override;

    string serialize() override;
    void deserialize(std::string g, std::string path = "") override;
    glm::mat4 GetMatrix();

    float* getVertices();
    std::size_t getIndicesSize();
    GLuint* getIndices();

    //SpriteComponent();
};
#endif