#include "../Graphics/StartEngineGraphics.h";
#include "../Graphics/AppSettings.h";
#include "../Components/SceneManager/SceneManager.h"

StartEngineGraphics* engine = new StartEngineGraphics();
AppSettings* settings = new AppSettings();
SceneManager* sceneManager = new SceneManager();

void main() {
	engine->create();
	settings->create();
	sceneManager->create();
	engine->StartEngine();

	while (!glfwWindowShouldClose(StartEngineGraphics::window))
	{
		engine->update();
	}

	sceneManager->release();
	settings->release();
	engine->release();
}