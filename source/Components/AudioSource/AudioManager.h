#pragma once
#include <inc/fmod.hpp>
#include <inc/fmod_errors.h>
#include <iostream>

using namespace FMOD;

class AudioManager
{
	static AudioManager* instance;
public:
	System* system = nullptr;
	FMOD_RESULT result = System_Create(&system);
	
	void create();
	void release();

	static AudioManager* GetManager() {
		return instance;
	}


	~AudioManager() {
		result = system->close();
		result = system->release();
	}
};