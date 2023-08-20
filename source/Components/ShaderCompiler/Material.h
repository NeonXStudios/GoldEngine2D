#pragma once
#include "../ECS/ECS.h"
#include "../../RequireLibs.h"
#include "../SceneManager/SceneManager.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"


class Material : public Component
{
private:
	VBO VBO1;
	EBO EBO1;
	VAO VAO1;

public:
	Shader shaderProgram;
	string vertexPath = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\MYFIRSTGAME\\assets\\shaders\\vertex.glsl";
	string fragmentPath = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\MYFIRSTGAME\\assets\\shaders\\fragment.glsl";
	GLuint vao, vbo, ebo;
	

	void init() override;



	void update() override;



	void draw() override;



	void clean() override;
};