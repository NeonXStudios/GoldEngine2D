#include "ECS.h"
#include "../../EngineBehaviour/GoldEngineLib.h"

void Entity::entityUpdate() {
    if (entity->parent != nullptr) {
        glm::vec3 PositionWithOffset = parent->transform->Position + entity->transform->LocalPosition;
        entity->transform->Position = PositionWithOffset;
    }
}
