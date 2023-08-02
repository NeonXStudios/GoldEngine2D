#include "Scene.h"
#include "../Sprite/SpriteComponent.h"
#include "../AudioSource/AudioSource.h"

Entity* newPlayerGen;

void Scene::start () {
	worldCamera->start();
	newPlayerGen = NewEntity();

	newPlayerGen->addComponent <SpriteComponent>();
	newPlayerGen->addComponent <AudioSource>();
	AudioSource* musicBG = &newPlayerGen->getComponent<AudioSource>();
	musicBG->SetVolumen (0.01f);
	musicBG->SetPan (1);
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