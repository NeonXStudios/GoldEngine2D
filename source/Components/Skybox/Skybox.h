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
	std::string facesCubemap[6] =
	{
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/right.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/left.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/top.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/bottom.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/front.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/back.jpg"
	};


	string vertexPath = "F:\\VISUAL STUDIO\\GoldEngine2D\\def\\shaders\\skybox.vert";
	string fragPath = "F:\\VISUAL STUDIO\\GoldEngine2D\\def\\shaders\\skybox.frag";
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;
	unsigned int skyboxEBO;
	unsigned int cubemapTexture;
	Shader* skyboxShader = nullptr;


	void init() override;



	void update() override;



	void draw() override;



	void clean() override;
};