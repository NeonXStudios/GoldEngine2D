#include "CRigidBody.h"


void CRigidBody::start() {

}


void CRigidBody::draw(Entity* owner) {
    EditorGUI::Text ("Rigid Body 2D");
    RigidBody& rigidBody = owner->getComponent<RigidBody>();
    ImGui::Spacing();
    ImGui::Spacing();


    rigidBody.Mass = EditorGUI::Float ("Mass", rigidBody.Mass);
    bool val = rigidBody.isStatic;
    ImGui::Checkbox("Static", &val);

    if (val != rigidBody.isStatic) {
        rigidBody.changeState (val);
        rigidBody.UpdateCollisions();
    }
    ImGui::Spacing();

    bool valFreezeX = rigidBody.FreezeX;
    ImGui::Checkbox("Freeze X", &valFreezeX);

    if (valFreezeX != rigidBody.FreezeX) {
        rigidBody.FreezeX = valFreezeX;
        rigidBody.UpdateCollisions();
    }

    bool valFreezeY = rigidBody.FreezeY;
    ImGui::Checkbox("Freeze Y", &valFreezeY);

    if (valFreezeY != rigidBody.FreezeY) {
        rigidBody.FreezeY = valFreezeY;
        rigidBody.UpdateCollisions();
    }

    ImGui::Spacing();

    bool valTrigger = rigidBody.isTrigger;
    ImGui::Checkbox("Trigger", &valTrigger);

    if (valTrigger != rigidBody.isTrigger) {
        rigidBody.isTrigger = valTrigger;
        rigidBody.UpdateCollisions();
    }
}