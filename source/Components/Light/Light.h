#pragma once
#include "../../EngineBehaviour/GoldEngineLib.h"

using namespace std;

enum TypeLight {
	DirectionLight,
	PointLight,
	SpotLight
};

class Light : public Component
{
public:
	glm::vec4 LightColor = glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f);
	float DistanceLight;

	//DIRECTION LIGHT SHADER
	string Directionfrag = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\LightShaders\\DirectionLight.frag";
	string Directionvert = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\LightShaders\\DirectionLight.vert";

	//SPOT LIGHT SHADER
	string Spotfrag = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\LightShaders\\SpotLight.frag";
	string Spotvert = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\LightShaders\\SpotLight.vert";

	//POINT LIGHT SHADER
	string Pointfrag = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\LightShaders\\PointLight.frag";
	string Pointvert = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\assets\\shaders\\LightShaders\\PointLight.vert";


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

	void preRenderShadow();



	std::string serialize() override {
		json data;
		data["wid"] = shadowMapWidth;
		return data;
	}


	void deserialize(std::string g, std::string path = "") override {

	}
};
