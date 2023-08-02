#include "RunEngine.h"

void RunEngine::StartGameEngine() {
	engine->create();
	settings->create();
	audioManager->create();
	sceneManager->create();
	engine->StartEngine();

	while (!glfwWindowShouldClose(StartEngineGraphics::window))
	{
		engine->update();
	}

	audioManager->release();
	sceneManager->release();
	settings->release();
	engine->release();
}