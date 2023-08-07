#pragma once
#include "../RequireLibs.h"
#include "../EngineBehaviour/EngineBehaviour.h"

class StartEngineGraphics
{
public:
	static StartEngineGraphics* instance;
	static GLFWwindow* window;
	static EngineBehaviour* engine;

	float time = 0.0f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;


	void create();
	void release();
	void update();
	void releasewindow();
	void StartEngine();
	
	//STATIC GLOBAL FUNCTIONS
	static void closeWindow();

	StartEngineGraphics* GetGraphics();
};