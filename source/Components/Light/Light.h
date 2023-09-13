#pragma once
#include "../../EngineBehaviour/GoldEngineLib.h"

using namespace std;

class Light : public Component
{
public:
	glm::vec4 LightColor = glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f);
	float DistanceLight;

	string frag = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\light.frag";
	string vert = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\light.vert";
	Shader* shader = nullptr;



	string ShadowMapVert = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\shadowMap.vert";
	string ShadowMapFrag = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\shadowMap.frag";
	Shader* shadowMapshader = nullptr;
	unsigned int shadowMapWidth = 2048;
	unsigned int shadowMapHeight = 2048;
	unsigned int shadowMap;
	unsigned int shadowMapFBO;

	glm::mat4 orthgonalProjection;
	glm::mat4 lightView;
	glm::mat4 lightProjection;


	void init() override;
	void update() override;
	void draw() override;
	void PreRender() override;
	void PostRender() override;



	std::string serialize() override {

		return "";
	}


	void deserialize(std::string g, std::string path = "") override {

	}
};
