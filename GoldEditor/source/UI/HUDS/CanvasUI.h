#pragma once
#include "../UIDrawer.h"

class CanvasUI : public UIDrawer
{
public:
	GLuint colorAndDepthTexture; // Variable para almacenar el ID de la textura combinada de color y profundidad
	GLuint depthRenderbuffer;    // Variable para almacenar el ID del renderbuffer de profundidad
	GLuint texture;
	GLuint framebuffer;       // Framebuffer Object
	GLuint depthTexture;      // Texture to capture depth
	ImVec2 imageSizeSCENE;
	ImVec2 imagePosition;

	bool isOpen;
	void start() override;
	void draw() override;
	void update() override;
	void lateupdate() override;
	void fixupdate() override;
};