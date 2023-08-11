#include "TriggerModule.h"



void TriggerModule::BeginContact(b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	for (Entity* entity : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
		RigidBody* rb = &entity->getComponent<RigidBody>();

		if (rb != nullptr) {
			if (rb->body == bodyA && rb->isTrigger) {
				for (Entity* entityB : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
					RigidBody* rbB = &entityB->getComponent<RigidBody>();
					if (rbB != nullptr && rbB->body == bodyB) {
						rbB->triggerOn();
						//std::cout << "El objeto que colision� es " << entityB->ObjectName << std::endl;
						// entity->OnTriggerStart(entityB);
					}
				}
			}

			if (rb->body == bodyB && rb->isTrigger) {
				for (Entity* entityA : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
					RigidBody* rbA = &entityA->getComponent<RigidBody>();
					if (rbA != nullptr && rbA->body == bodyA) {
						rbA->triggerOn();
						//std::cout << "El objeto que colision� es " << entityA->ObjectName << std::endl;
						// entity->OnTriggerStart(entityA);
					}
				}
			}
		}
	}
}

void TriggerModule::EndContact (b2Contact* contact) {
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	for (Entity* entity : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
		RigidBody* rb = &entity->getComponent<RigidBody>();

		if (rb != nullptr) {
			if (rb->body == bodyA && rb->isTrigger) {
				for (Entity* entityB : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
					RigidBody* rbB = &entityB->getComponent<RigidBody>();
					if (rbB != nullptr && rbB->body == bodyB) {
						rbB->triggerOff();
						//std::cout << "El objeto que se fue es " << entityB->ObjectName << std::endl;
						// entity->OnTriggerStart(entityB);
					}
				}
			}

			if (rb->body == bodyB && rb->isTrigger) {
				for (Entity* entityA : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
					RigidBody* rbA = &entityA->getComponent<RigidBody>();
					if (rbA != nullptr && rbA->body == bodyA) {
						rbA->triggerOff();
						//std::cout << "El objeto que se fue es " << entityA->ObjectName << std::endl;
						// entity->OnTriggerStart(entityA);
					}
				}
			}
		}
	}
}