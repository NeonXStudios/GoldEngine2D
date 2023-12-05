#pragma once
#include "../../source/EngineBehaviour/GoldEngineLib.h"


#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

/// <summary>
/// UI COMPONENTS
/// </summary>
#include "UIBehaviour.h"
#include "ComponentsUI/UIButton.h"


using namespace std;

class Canvas : public Component
{
public:
	GLuint uiFramebuffer;
	GLuint uiTexture;
	unsigned int texture;
	unsigned int framebuffer;       // Framebuffer Object
	unsigned int depthTexture;      // Texture to capture depth
	GLuint colorAndDepthTexture; // Variable para almacenar el ID de la textura combinada de color y profundidad
	GLuint depthRenderbuffer;    // Variable para almacenar el ID del renderbuffer de profundidad


	std::vector<UIBehaviour*> Data = std::vector<UIBehaviour*>();

	void init() override;
	void update() override;
	void draw() override;
	void clean() override;
	void PreRender() override;
	void PostRender() override;

	string serialize() override;
	void deserialize(std::string g, std::string path = "") override;
};