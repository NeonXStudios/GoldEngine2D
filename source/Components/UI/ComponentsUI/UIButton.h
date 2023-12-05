#pragma once
#include "../UIBehaviour.h"


class UIButton : public UIBehaviour
{
public:
	string VertexPath = "shaders/UI/UIVertex.vert";
	string FragmentPath = "shaders/UI/UIFrag.frag";

	GLD::Model* ourmodel;
	Shader* ourShader = nullptr;
	GLuint texture;
	GLuint VAO, VBO;


	float widthTXT;
	float heightTXT;
	 
	void start() override;
	void draw() override;
	void CompilerShaders() override;
	void onClick() override;
	void LoadTexture (string path = "UI/button.png");
};