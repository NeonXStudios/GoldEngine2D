#pragma once
#include <GoldEngineLib.h>

class GDGizmos
{
private:
    //std::vector<glm::vec3> vertices;
    //std::vector<glm::vec3> colors;

public:
    static GDGizmos* instance;
    Shader* shader = nullptr;
    void start      ();
    void Draw       ();
    
    //GIZMOS
    void DrawCube   (const glm::vec3& position, const glm::vec3& size, const glm::vec3& color);
    void DrawSphere (const glm::vec3& position, const float radius, const glm::vec3& color);


    void AddLine    (const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);
    Entity* entity = new Entity();
    unsigned int VBO, VAO, EBO;
    unsigned int texture;
    unsigned int compileShader(unsigned int type, const char* source);
    unsigned int vertexShader, fragmentShader, shaderProgram;


    void create  ();
    void release ();
};