#pragma once
#include <iostream>
#include "../ECS/ECS.h"
#include "../../RequireLibs.h"

using namespace std;

class Skybox : public Component
{
public:
    const char* vertexShaderSource2 = R"(
    #version 330 core
layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos = projection * view * vec4(aPos, 1.0f);
    // Having z equal w will always result in a depth of 1.0f
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    // We want to flip the z axis due to the different coordinate systems (left hand vs right hand)
    texCoords = vec3(aPos.x, aPos.y, -aPos.z);
}    
)";

    const char* fragmentShaderSource2 = R"(
    #version 330 core
out vec4 FragColor;

in vec3 texCoords;
E
uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, texCoords);
}
)";

	std::string facesCubemap[6] =
	{
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/right.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/left.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/top.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/bottom.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/front.jpg",
		"F:\\VISUAL STUDIO\\GoldEngine2D\\BuildHub\\Editor\\skybox/back.jpg"
	};


	void init() override;



	void update() override;



	void draw() override;



	void clean() override;
};