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

    Transform* sprite = entity->transform;
    Transform* parentSprite = parent->transform;

    float parentGlobalX = parentSprite->Position.x;
    float parentGlobalY = parentSprite->Position.y;
    float parentGlobalZ = parentSprite->Position.z;

    float childLocalX = sprite->LocalPosition.x;
    float childLocalY = sprite->LocalPosition.y;
    float childLocalZ = sprite->LocalPosition.z;

    if (entity->hasComponent<RigidBody>()) {
        RigidBody& rigi = entity->getComponent<RigidBody>();
        if (!rigi.isStatic) {
            //sprite->ObjectPosition.x = parentGlobalX + childLocalX;
            //sprite->ObjectPosition.y = parentGlobalY + childLocalY;
            // Actualiza la LocalPosition con respecto al nuevo global
            sprite->LocalPosition.x = sprite->Position.x - parentGlobalX;
            sprite->LocalPosition.y = sprite->Position.y - parentGlobalY;
            sprite->LocalPosition.z = sprite->Position.z - parentGlobalZ;


            rigi.position.x = parentGlobalX + childLocalX;
            rigi.position.y = parentGlobalY + childLocalY;
            //rigi.position.z = parentGlobalZ + childLocalZ;
        }
        else {
            sprite->Position.x = parentGlobalX + childLocalX;
            sprite->Position.y = parentGlobalY + childLocalY;
            // Actualiza la LocalPosition con respecto al nuevo global
            sprite->LocalPosition.x = sprite->Position.x - parentGlobalX;
            sprite->LocalPosition.y = sprite->Position.y - parentGlobalY;

            //rigi.position.x = parentGlobalX + childLocalX;
            //rigi.position.y = parentGlobalY + childLocalY;
        }
    }
    else {
        sprite->Position.x   = parentGlobalX + childLocalX;
        sprite->Position.y   = parentGlobalY + childLocalY;
        //sprite->Position.z = parentGlobalZ + childLocalZ;

        // Actualiza la LocalPosition con respecto al nuevo global
        sprite->LocalPosition.x = sprite->Position.x - parentGlobalX;
        sprite->LocalPosition.y = sprite->Position.y - parentGlobalY;
        sprite->LocalPosition.z = sprite->Position.z - parentGlobalZ;
    }
}