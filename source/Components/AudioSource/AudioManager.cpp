#include "AudioManager.h"

using namespace std;
AudioManager* AudioManager::instance = nullptr;

void AudioManager::create() {
	if (AudioManager::instance) throw std::exception("AudioManager already created.");
	AudioManager::instance = new AudioManager();
	std::cout << "AudioManager Created" << endl;
}


void AudioManager::release() {
	if (!AudioManager::instance) return;
	delete AudioManager::instance;
}