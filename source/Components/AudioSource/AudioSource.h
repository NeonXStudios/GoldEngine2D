#pragma once
#include "AudioManager.h"
#include <iostream>
#include "../ECS/ECS.h"
#include "../FileSystem/FileSystem.h" 


using namespace std;
using namespace FMOD;

class AudioSource : public Component
{
	Sound* sound = nullptr;
	Channel* channel = nullptr;
	bool IsSpatial3D = true;
	FMOD_RESULT result;
	float pan = 0;
	float Volumen = 1;

public:
	std::string AudioPath = "";
	float minDistance = 5;
	float maxDistance = 10;

	void init () override {
		FMOD_RESULT initResult = AudioManager::GetManager()->result;
		if (initResult != FMOD_OK) {
			std::cout << "ERROR: FMOD initialization failed" << std::endl;
		}
		else {
			// FMOD inicializado correctamente, ahora carga y reproduce el sonido.
			FMOD_RESULT loadResult = AudioManager::GetManager()->system->createSound(FileSystem::GetAsset(AudioPath).c_str(), FMOD_3D | FMOD_3D_LINEARROLLOFF, nullptr, &sound);

			if (loadResult != FMOD_OK) {
				std::cout << "Failed to load audio: " << FMOD_ErrorString(loadResult) << std::endl;
			}
			else {
				// Reproduce el sonido.
				FMOD_RESULT playResult = AudioManager::GetManager()->system->playSound(sound, nullptr, false, &channel);
				channel->setVolume (0);
				if (playResult != FMOD_OK) {
					std::cout << "Failed to play audio: " << FMOD_ErrorString(playResult) << std::endl;
				}
				else {
					std::cout << "************* Audio component started successfully..." << std::endl;
				}
			}
		}


		channel->set3DMinMaxDistance(minDistance, maxDistance);
	}

	void Stop() {
		channel->stop();
	}

	void Reset() {
		channel->stop();
		init();
	}


	void SetPan (float panSide) {
		pan = panSide;
		channel->setPan (pan);
	}

	float GetPan() {
		return pan;
	}

	void SetVolumen (float newVolumen) {
		Volumen = newVolumen;
		channel->setVolume(Volumen);
	}

	float* GetVolumen() {
		float g;
		channel->getVolume (&g);
		return &g;
	}

	bool* IsPlaying () {
		bool ispl;
		channel->isPlaying (&ispl);
		return &ispl;
	}

	void SetPauseState (bool pauseState) {
		channel->setPaused (pauseState);
	}

	void update() override {

		if (IsSpatial3D && SceneManager::GetSceneManager()->OpenScene->worldCamera != nullptr && entity != nullptr) {
			Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;

			FMOD_VECTOR position = { entity->transform->Position.x, entity->transform->Position.y, SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition.z};
			FMOD_VECTOR velocity = { cam->cameraVelocity.x, cam->cameraVelocity.y, cam->cameraVelocity.z };
			FMOD_VECTOR forward =  { cam->cameraFront.x, cam->cameraFront.y, cam->cameraFront.z };
			FMOD_VECTOR up = { cam->cameraUp.x, cam->cameraUp.y, cam->cameraUp.z };

			channel->set3DMinMaxDistance(minDistance, maxDistance);
			FMOD_RESULT result = channel->set3DAttributes(&position, 0);

			if (result != FMOD_OK) {
				//std::cout << "3D AUDIO LOAD" << std::endl;
			}

		}

			SetVolumen (Volumen);
	}

	void clean() override {
		channel->stop();
		AudioManager::GetManager()->result = sound->release();
	}

	string serialize() override;
	void deserialize(std::string g, std::string path = "") override;

};