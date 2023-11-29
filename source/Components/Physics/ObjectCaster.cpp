#include "ObjectCaster.h"

bool ObjectCaster::MouseCast(glm::vec2 coords, CastData* data) {
    float closestZ = std::numeric_limits<float>::lowest(); // Inicializa con el valor mínimo posible
    Entity* closestObject = nullptr;

    for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
        Entity* objD = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];

        glm::vec3& obj = objD->entity->transform->Position;
        float objWidth = objD->entity->transform->Scale.x;
        float objHeight = objD->entity->transform->Scale.y;

        float radians = objD->entity->transform->Rotation.x * (b2_pi / 180.0f);

        glm::vec2 localPoint = RotatePoint(coords, obj, radians);

        // Solo considera la coordenada Z para determinar qué objeto está más adelante
        if (localPoint.x >= obj.x - objWidth && localPoint.x <= obj.x + objWidth &&
            localPoint.y >= obj.y - objHeight && localPoint.y <= obj.y + objHeight) {

            // Comprueba si la coordenada Z es mayor que la más cercana hasta ahora
            if (obj.z > closestZ) {
                closestZ = obj.z;
                closestObject = objD;
            }
        }
    }

    if (closestObject != nullptr) {
        data->object = closestObject;
        return true;
    }

    return false;
}


//bool ObjectCaster::MouseCast (glm::vec2 coords, CastData* data) {
//    for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
//        Entity* objD = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];
//
//        glm::vec3& obj = objD->entity->transform->Position;
//        float objWidth = objD->entity->transform->Scale.x;
//        float objHeight = objD->entity->transform->Scale.y;
//
//        float radians = objD->entity->transform->Rotation.x * (b2_pi / 180.0f);
//
//        glm::vec2 localPoint = RotatePoint(coords, obj, radians);
//
//        glm::vec2 rotatedBoxMin(obj.x - objWidth, obj.y - objHeight);
//        glm::vec2 rotatedBoxMax(obj.x + objWidth, obj.y + objHeight);
//        glm::vec2 dragOffset;
//
//
//        //Comprueba si el punto rotado está dentro de la caja delimitadora rotada
//        if (localPoint.x >= rotatedBoxMin.x && localPoint.x <= rotatedBoxMax.x &&
//            localPoint.y >= rotatedBoxMin.y && localPoint.y <= rotatedBoxMax.y) {
//
//            data->object = objD;
//            return true;
//        } 
//    }
//
//    return false;
//}

glm::vec2 ObjectCaster::RotatePoint(const glm::vec2& point, const glm::vec2& center, float angle) {
    glm::vec2 rotatedPoint;
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);

    rotatedPoint.x = center.x + (point.x - center.x) * cosTheta - (point.y - center.y) * sinTheta;
    rotatedPoint.y = center.y + (point.x - center.x) * sinTheta + (point.y - center.y) * cosTheta;

    return rotatedPoint;
}