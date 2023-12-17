#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../ShaderCompiler/Shader.h"
#include <stb_image.h>
#include "../FileSystem/FileSystem.h"

#define MODELCLASS_H
#include "../Models/Model.h"

using namespace std;

enum AnchorUI {
	Left,
	Right,
	Top,
	Bottom,
	Center,
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	None
};

class UIBehaviour
{
public:
	glm::quat rotation;
	glm::mat4 Matrix = glm::mat4(1.0f);
	glm::mat4 MatrixLocal = glm::mat4(1.0f);
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 LocalPosition = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(100.0f, 100.0f, 1.0f);
	glm::vec3 Offset = glm::vec3(0.0f, 0.0f, 0.0f);

	float normalXSize = 0;
	float NormalYSize = 0;

public:
	AnchorUI currentAnchor = AnchorUI::None;
	glm::vec3 RectPosition;
	glm::vec3 RectScale;
	glm::vec3 RectRot;

	string VertexPath = "shaders/UI/UIVertex.vert";
	string FragmentPath = "shaders/UI/UIFrag.frag";

	Shader* shader = nullptr;

	virtual void start() = 0;
	virtual void draw() = 0;
	virtual void CompilerShaders() = 0;
	virtual void onClick() = 0;
};