#pragma once
#include "../ECS/ECS.h"
#include "../../RequireLibs.h"
#include "../ShaderCompiler/Shader.h"
#include "../SceneManager/SceneManager.h"
#include <iostream>

using namespace std;

class Skybox : public Component
{
public:
	string skyboxPath = "F:\\VISUAL STUDIO\\GoldEngine2D\\def\\shaders\\skybox.vert";

	string vertexPath = "F:\\VISUAL STUDIO\\GoldEngine2D\\def\\shaders\\skybox.vert";
	string fragPath = "F:\\VISUAL STUDIO\\GoldEngine2D\\def\\shaders\\skybox.frag";
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;
	unsigned int skyboxEBO;
	unsigned int cubemapTexture;
	Shader* skyboxShader = nullptr;
	unsigned int skyboxTexture;


	void init() override;



	void update() override;



	void draw() override;



	void clean() override;
};