#include "Scene.h"
#include "../Sprite/SpriteComponent.h"
#include "../AudioSource/AudioSource.h"
#include "../Physics/TriggerModule.h"


void Scene::start() {
	CreateGravity();
	worldCamera->start();
}

void Scene::update() {
	worldCamera->update();

	if (GravityWorld != nullptr && GravityWorld->GetBodyCount() > 0) {
		b2Body* body = GravityWorld->GetBodyList();
		float timeStep = 1.0f / 60;
		GravityWorld->Step(timeStep, 6, 2);
		body->GetNext();
	}

	for (Entity* ents : objectsInScene) {
		ents->entity = ents;
		ents->update();
	}
}

void Scene::release() {

}


void Scene::CreateGravity() {
	b2Vec2 gravity(0, 20);
	GravityWorld = new b2World(gravity);

	if (GravityWorld != nullptr) {
		//TriggerData* data = new TriggerData();
		TriggerModule* triggerData = new TriggerModule();
		GravityWorld->SetContactListener(triggerData);
		std::cout << "Gravity created " << endl;
	}
}