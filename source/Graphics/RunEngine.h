#include "../Graphics/StartEngineGraphics.h";
#include "../Graphics/AppSettings.h";
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/AudioSource/AudioManager.h"
#include "../EngineBehaviour/EngineBehaviour.h"






class RunEngine {
public:
	StartEngineGraphics* engine = new StartEngineGraphics();
	AppSettings* settings = new AppSettings();
	SceneManager* sceneManager = new SceneManager();
	AudioManager* audioManager = new AudioManager();

	void StartGameEngine (EngineBehaviour* game) {
		engine->create();

		//CREATE APP SETTINGS
		settings->create();

		//CREATE AUDIO MANAGER
		audioManager->create();

		//CREATE SCENEMANAGER INSTANCE
		sceneManager->create();

		//LOAD GAME WINDOW
		engine->engine = game;

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
	}
};