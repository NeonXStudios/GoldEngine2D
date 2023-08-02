#include "SceneManager.h"
#include <iostream>;

using namespace std;


SceneManager* SceneManager::instance = nullptr;

void SceneManager::create()
{
	if (SceneManager::instance) throw std::exception("SceneManager already created.");
	SceneManager::instance = new SceneManager();
	std::cout << "SceneManager Created" << endl;
}



void SceneManager::release()
{
	if (!SceneManager::instance) return;
	delete SceneManager::instance;
}


SceneManager* SceneManager::GetSceneManager() {
	return instance;
}