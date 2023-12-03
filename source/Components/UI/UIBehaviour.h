#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "../ShaderCompiler/Shader.h"
#include <stb_image.h>
#include "../FileSystem/FileSystem.h"

using namespace std;

class UIBehaviour
{
public:
	glm::vec3 RectPosition;
	glm::vec3 RectScale;
	glm::vec3 RectRot;

	string VertexPath = "shaders/UI/UIVertex.vert";
	string FragmentPath = "shaders/UI/UIFrag.frag";

	Shader* shader = nullptr;

	virtual void start() = 0;
	virtual void draw() = 0;
	virtual void CompilerShaders() = 0;
};