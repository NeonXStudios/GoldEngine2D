#include "ECS.h"
#include "../../EngineBehaviour/GoldEngineLib.h"

/*
void Entity::addGroup(Group mGroup)
{
	groupBitset[mGroup] = true;
	//manager.AddToGroup (this, mGroup);
}
*/


void Entity::entityUpdate() {
    if (entity == nullptr) { return; }

    if (parent == nullptr) { return; }
    if (!entity->hasComponent<SpriteComponent>()) { return; }

    if (!parent->hasComponent<SpriteComponent>()) { return; }

    SpriteComponent* sprite = &entity->getComponent<SpriteComponent>();
    SpriteComponent* parentSprite = &parent->getComponent<SpriteComponent>();

    float parentGlobalX = parentSprite->ObjectPosition.x;
    float parentGlobalY = parentSprite->ObjectPosition.y;

    float childLocalX = sprite->LocalPosition.x;
    float childLocalY = sprite->LocalPosition.y;

    if (entity->hasComponent<RigidBody>()) {
        RigidBody& rigi = entity->getComponent<RigidBody>();
        if (!rigi.isStatic) {
            //sprite->ObjectPosition.x = parentGlobalX + childLocalX;
            //sprite->ObjectPosition.y = parentGlobalY + childLocalY;
            // Actualiza la LocalPosition con respecto al nuevo global
            sprite->LocalPosition.x = sprite->ObjectPosition.x - parentGlobalX;
            sprite->LocalPosition.y = sprite->ObjectPosition.y - parentGlobalY;


            rigi.position.x = parentGlobalX + childLocalX;
            rigi.position.y = parentGlobalY + childLocalY;
        }
        else {
            sprite->ObjectPosition.x = parentGlobalX + childLocalX;
            sprite->ObjectPosition.y = parentGlobalY + childLocalY;
            // Actualiza la LocalPosition con respecto al nuevo global
            sprite->LocalPosition.x = sprite->ObjectPosition.x - parentGlobalX;
            sprite->LocalPosition.y = sprite->ObjectPosition.y - parentGlobalY;

            //rigi.position.x = parentGlobalX + childLocalX;
            //rigi.position.y = parentGlobalY + childLocalY;
        }
    }
    else {
        sprite->ObjectPosition.x = parentGlobalX + childLocalX;
        sprite->ObjectPosition.y = parentGlobalY + childLocalY;
        // Actualiza la LocalPosition con respecto al nuevo global
        sprite->LocalPosition.x = sprite->ObjectPosition.x - parentGlobalX;
        sprite->LocalPosition.y = sprite->ObjectPosition.y - parentGlobalY;
    }
}