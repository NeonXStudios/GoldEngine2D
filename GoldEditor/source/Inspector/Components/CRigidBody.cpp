#include "CRigidBody.h"


void CRigidBody::start() {

}


void CRigidBody::draw(Entity* owner) {
    RigidBody& rigidBody = owner->getComponent<RigidBody>();

    bool val = rigidBody.isStatic;
    ImGui::Checkbox("Static", &val);

    if (val != rigidBody.isStatic) {
        rigidBody.changeState (val);
    }
}