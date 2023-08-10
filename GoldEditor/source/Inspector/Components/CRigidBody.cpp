#include "CRigidBody.h"


void CRigidBody::start() {

}


void CRigidBody::draw(Entity* owner) {
    EditorGUI::Text ("Rigid Body 2D");
    RigidBody& rigidBody = owner->getComponent<RigidBody>();

    bool val = rigidBody.isStatic;
    ImGui::Checkbox("Static", &val);

    if (val != rigidBody.isStatic) {
        rigidBody.changeState (val);
    }
}