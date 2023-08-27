#include "CBoxCollider3D.h"


void CBoxCollider3D::start() {

}


void CBoxCollider3D::draw(Entity* owner) {
	ImGui::Button("Box Collider3D", ImVec2(ImGui::GetContentRegionAvail().x, 20));
	ImGui::Spacing();

	owner->getComponent <BoxCollider>().boxSize = EditorGUI::Vector3 ("Box Size", owner->getComponent <BoxCollider>().boxSize);
}