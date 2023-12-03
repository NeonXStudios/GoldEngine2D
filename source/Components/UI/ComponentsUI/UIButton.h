#pragma once
#include "../UIBehaviour.h"

class UIButton : public UIBehaviour
{
public:
	string VertexPath = "shaders/UI/UIVertex.vert";
	string FragmentPath = "shaders/UI/UIFrag.frag";

	Shader* shader = nullptr;
	GLuint texture;
	GLuint VAO, VBO;

	void start() override;
	void draw() override;
	void CompilerShaders() override;
	void LoadTexture (string path = "UI/button.png");
};