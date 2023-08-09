#pragma once
#include <iostream>
#include "AudioManager.h"
#include "../ECS/ECS.h"

using namespace FMOD;

class AudioSource : public Component
{
	Sound* sound = nullptr;
	Channel* channel = nullptr;

public:
	std::string AudioPath = "game/assets/music/HideYourHeart-NCS.mp3";
	void init () override {

		if (AudioManager::GetManager()->result != FMOD_OK) {
			std::cout << "AUDIO MANAGER NOT STARTED" << std::endl;
		}
		else {
			std::cout << "AudioManager Load 1 Completed..." << std::endl;
		}
		

		AudioManager::GetManager()->result = AudioManager::GetManager()->system->init (32, FMOD_INIT_NORMAL, nullptr);

		if (AudioManager::GetManager()->result != FMOD_OK) {
			std::cout << "AUDIO MANAGER NOT STARTED" << std::endl;
		}
		else {
			std::cout << "AudioManager Load 2 Completed..." << std::endl;
		}

		AudioManager::GetManager()->result = AudioManager::GetManager()->system->createSound (AudioPath.c_str(), FMOD_DEFAULT, nullptr, &sound);


		AudioManager::GetManager()->result = AudioManager::GetManager()->system->playSound (sound, nullptr, false, &channel);

		if (AudioManager::GetManager()->result != FMOD_OK) {
			std::cout << "AUDIO MANAGER NOT STARTED" << std::endl;
		}
		else {
			std::cout << "Audio component started successfully..." << std::endl;
		}
		SetVolumen (1.0f);
	}


	void SetPan (float panSide) {
		channel->setPan (panSide);
	}

	void SetVolumen (float newVolumen) {
		channel->setVolume(newVolumen);
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

	}

	void clean() override {
		channel->stop();
		AudioManager::GetManager()->result = sound->release();
	}
};