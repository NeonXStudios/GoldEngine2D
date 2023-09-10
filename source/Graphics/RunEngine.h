#include "../Graphics/StartEngineGraphics.h";
#include "../Graphics/AppSettings.h";
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/AudioSource/AudioManager.h"
#include "../EngineBehaviour/EngineBehaviour.h"
#include <iostream>

class RunEngine {
public:
	StartEngineGraphics* engine = new StartEngineGraphics();
	AppSettings* settings = new AppSettings();
	SceneManager* sceneManager = new SceneManager();
	AudioManager* audioManager = new AudioManager();
	int frameCount = 0;
	double prevTime;


	void StartGameEngine (EngineBehaviour* game, bool runGame) {
		engine->create();

		//CREATE APP SETTINGS
		settings->create();
		AppSettings::gameRunning = runGame;

		//CREATE AUDIO MANAGER
		//audioManager->create();
		audioManager->create();
		audioManager->StartSystem();

		//CREATE SCENEMANAGER INSTANCE
		sceneManager->create();

		//LOAD GAME WINDOW
		engine->engine = game;

		//START THE ENGINE
		engine->StartEngine();

		prevTime = glfwGetTime();
		double targetFrameTime = 1.0 / AppSettings::getTargetFrame();
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);

		///FPS LIMIT
		while (!glfwWindowShouldClose(StartEngineGraphics::window))
		{
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - prevTime;

			// Limitar el tiempo de fotograma si es necesario
			if (deltaTime < targetFrameTime)
			{
				double sleepTime = targetFrameTime - deltaTime;
				// Con glfwWaitEventsTimeout, la aplicación entra en modo de espera hasta que se alcance el tiempo objetivo
				glfwWaitEventsTimeout(sleepTime);
			}

			engine->update();
		}

		audioManager->release();
		sceneManager->release();
		settings->release();
		engine->release();
	}


	void ShowFPSConsoleDebug () {
		// Calcula y muestra los FPS fuera del bucle de limitación de FPS
		double fps = 1.0 / (glfwGetTime() - prevTime);
		printf("FPS: %.2f\n", fps);

		prevTime = glfwGetTime();
	}
};