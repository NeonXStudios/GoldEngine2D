#pragma once
#include "../ECS/ECS.h"
#include "../../RequireLibs.h"
#include "../ShaderCompiler/Shader.h"
#include "../SceneManager/SceneManager.h"
#include "../SaveSystem/CheckVar.h"
#include "../FileSystem/FileSystem.h"
#include "../Systems/SystemsEvents.h"
#include <iostream>

using namespace std;

class Skybox : public Component
{
public:
	string modelPath = "E:\\VISUAL STUDIO\\GoldEngine2D\\def\\models\\SkySphere.fbx";


	string TexturePath = "skybox/sky360.png";
	string VertexPath = "shaders/skyboxvert.glsl";
	string FragmentPath = "shaders/skyboxfrag.glsl";

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 LocalPosition = glm::vec3(1.0f, 1.0f, 1.0f);


	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(10.0f, 10.0f, 10.0f);

	glm::mat4 Matrix = glm::mat4(1.0f);
	glm::quat rotation;

	Shader* ourShader = nullptr;
	GLD::Model* ourmodel = nullptr;
	unsigned int texture;


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

	void PreRender() override;
	void PostRender() override;

	glm::mat4 GetMatrix();
};