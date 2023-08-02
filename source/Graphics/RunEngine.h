#include "../Graphics/StartEngineGraphics.h";
#include "../Graphics/AppSettings.h";
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/AudioSource/AudioManager.h"

StartEngineGraphics* engine = new StartEngineGraphics();
AppSettings* settings = new AppSettings();
SceneManager* sceneManager = new SceneManager();
AudioManager* audioManager = new AudioManager();



class RunEngine {
public:
	void StartGameEngine() {
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
};