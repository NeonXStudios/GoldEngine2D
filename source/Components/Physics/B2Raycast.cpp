#include "B2Raycast.h"
#include "../SceneManager/SceneManager.h"
#include "RigidBody.h"

float B2Raycast::ReportFixture (b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) {
    b2Body* body = fixture->GetBody();

    //// Aquí puedes realizar acciones con el resultado del raycast
    //std::cout << "Ray hit fixture." << std::endl;
    //std::cout << "Body ID: " << body->GetUserData() << std::endl;
    //std::cout << "Fraction: " << fraction << std::endl;
    //std::cout << "Point: (" << point.x << ", " << point.y << ")" << std::endl;
    //std::cout << "Normal: (" << normal.x << ", " << normal.y << ")" << std::endl;

    //// Continuar con el siguiente fixture

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