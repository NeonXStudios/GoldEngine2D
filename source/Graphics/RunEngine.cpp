#include "RunEngine.h"

StartEngineGraphics* engine = new StartEngineGraphics();
AppSettings* settings = new AppSettings();
SceneManager* sceneManager = new SceneManager();
AudioManager* audioManager = new AudioManager();


int main() {
	//CREATE ENGINE INSTANCE
	engine->create();

	//CREATE APP SETTINGS
	settings->create();

	//CREATE AUDIO MANAGER
	audioManager->create();

	//CREATE SCENEMANAGER INSTANCE
	sceneManager->create();

	//LOAD GAME WINDOW
	//engine->engine = game;

	//START THE ENGINE
	engine->StartEngine();

	while (!glfwWindowShouldClose(StartEngineGraphics::window))
	{
		engine->update();
	}

	audioManager->release();
	sceneManager->release();
	settings->release();
	engine->release();
	return 0;
}