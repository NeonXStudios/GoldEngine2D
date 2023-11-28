#include "B2Raycast.h"
#include "../SceneManager/SceneManager.h"
#include "RigidBody.h"

float B2Raycast::ReportFixture (b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
    b2Body* body = fixture->GetBody();


    for (Entity* objs : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
        if (objs->hasComponent<RigidBody>()) {
            if (body == objs->getComponent<RigidBody>().body) {
                std::cout << "Body Found: " << objs->ObjectName << std::endl;
            }
        } 
    }

    //std::cout << "Object Cast " << body->GetPosition().x << " | " << body->GetPosition().y << std::endl;
    return 1.0f;
}