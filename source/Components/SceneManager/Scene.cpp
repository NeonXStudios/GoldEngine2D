#include "Scene.h"
#include "../Sprite/SpriteComponent.h"
#include "../AudioSource/AudioSource.h"

void Scene::start () {
	objectsInScene = std::vector<Entity*>();
	worldCamera->start();
}

void Scene::update () {
	worldCamera->update();
	for (Entity* ents : objectsInScene) {
		ents->update();
	}
}

void Scene::release () {

}

