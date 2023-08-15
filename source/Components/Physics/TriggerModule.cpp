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
					    rb->triggerOn (rbB->entity);


						//std::cout << "1: Mi objeto de trigger es  " << rb->entity->ObjectName << std::endl;
						//std::cout << "1: El objeto que colisiono es " << entityB->ObjectName << std::endl;
					}
				}
			}

			if (rb->body == bodyB && rb->isTrigger) {
				for (Entity* entityA : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
					RigidBody* rbA = &entityA->getComponent<RigidBody>();
					if (rbA != nullptr && rbA->body == bodyA) {
						rb->triggerOn(rbA->entity);


						//std::cout << "1: Mi objeto de trigger es  " << rb->entity->ObjectName << std::endl;
						//std::cout << "1: El objeto que colisiono es " << entityA->ObjectName << std::endl;
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
						rb->triggerOff(rbB->entity);


						//std::cout << "1: Mi objeto de trigger es  " << rb->entity->ObjectName << std::endl;
						//std::cout << "1: El objeto que colisiono es " << entityB->ObjectName << std::endl;
					}
				}
			}

			if (rb->body == bodyB && rb->isTrigger) {
				for (Entity* entityA : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
					RigidBody* rbA = &entityA->getComponent<RigidBody>();
					if (rbA != nullptr && rbA->body == bodyA) {
						rb->triggerOff(rbA->entity);


						//std::cout << "1: Mi objeto de trigger es  " << rb->entity->ObjectName << std::endl;
						//std::cout << "1: El objeto que colisiono es " << entityA->ObjectName << std::endl;
					}
				}
			}
		}
	}
}