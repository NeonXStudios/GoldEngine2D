#include "SceneManager.h"
#include <iostream>;
#include <string>

using namespace std;


SceneManager* SceneManager::instance = nullptr;

void SceneManager::create()
{
	if (SceneManager::instance) throw std::exception("SceneManager already created.");
	SceneManager::instance = new SceneManager();
	std::cout << "SceneManager Created" << endl;
	SceneManager::GetSceneManager()->OpenScene = new Scene();
}



void SceneManager::release()
{
	if (!SceneManager::instance) return;
	delete SceneManager::instance;
}


SceneManager* SceneManager::GetSceneManager() {
	return instance;
}

Entity* SceneManager::NewEntity() {
	Entity* newObj = new Entity();

	if (&newObj->getComponent<SpriteComponent>() == nullptr) {
		newObj->addComponent<SpriteComponent>();
	}


	OpenScene->objectsInScene.push_back(newObj);
	newObj->ObjectName = "New Entity " + std::to_string (OpenScene->objectsInScene.size() + 1);
	return newObj;
}


Entity* SceneManager::GetObjectByID (int id) {
	// Asegúrate de que OpenScene y objectsInScene no sean nulos
	if (OpenScene && OpenScene->objectsInScene.size() > 0) {
		// Busca el objeto con el ID deseado en el vector de objetos de la escena
		for (Entity* obj : OpenScene->objectsInScene) {
			if (obj->objectID == id) {
				return obj; // Se encontró el objeto con el ID especificado
			}
		}
	}
	return nullptr; // No se encontró el objeto con el ID especificado o el vector estaba vacío
}