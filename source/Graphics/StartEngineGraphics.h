#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class StartEngineGraphics
{
public:
	static StartEngineGraphics* instance;
	static GLFWwindow* window;
	float time = 0.0f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;


	void create();
	void release();
	void update();
	void releasewindow();
	int StartEngine();

	StartEngineGraphics* GetGraphics();
};