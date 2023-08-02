#include "Scene.h"
#include "../Sprite/SpriteComponent.h"

Entity* newPlayerGen;

void Scene::start () {
	worldCamera->start();
	newPlayerGen = NewEntity();

	newPlayerGen->addComponent <SpriteComponent>();
}

void Scene::update () {
	worldCamera->update();

	for (Entity* ents : objectsInScene) {
		ents->update();
	}
}

void Scene::release () {

}

Entity* Scene::NewEntity() {
	Entity* newObj = new Entity ();
	objectsInScene.push_back (newObj);
	return newObj;
}