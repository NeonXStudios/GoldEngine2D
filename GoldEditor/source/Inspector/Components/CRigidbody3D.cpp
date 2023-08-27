#include "CRigidbody3D.h"

void CRigidbody3D::start() {

}


void CRigidbody3D::draw(Entity* owner) {
	ImGui::Button ("Rigidbody3D", ImVec2 (ImGui::GetContentRegionAvail().x, 20));
	ImGui::Spacing();
	owner->entity->getComponent <Rigidbody3d>().mass = EditorGUI::Float ("Mass", owner->entity->getComponent <Rigidbody3d>().mass);
	ImGui::Separator();





	bool isStatic = EditorGUI::Toggle("Is Kinematic", owner->entity->getComponent <Rigidbody3d>().isStatic);
	bool useGrav = EditorGUI::Toggle ("Use Gravity", owner->entity->getComponent <Rigidbody3d>().useGravity);
	owner->entity->getComponent <Rigidbody3d>().isStatic   = isStatic;
	owner->entity->getComponent <Rigidbody3d>().useGravity = useGrav;



	ImGui::NewLine();
	ImGui::Separator();
	ImGui::SameLine();
	ImGui::PushID ("FRPos");
	ImGui::Text ("Freeze Position");
	ImGui::SameLine();
	bool posX = EditorGUI::Toggle("X", owner->entity->getComponent <Rigidbody3d>().freezePosX);
	ImGui::SameLine();
	bool posY = EditorGUI::Toggle("Y", owner->entity->getComponent <Rigidbody3d>().freezePosY);
	ImGui::SameLine();
	bool posZ = EditorGUI::Toggle("Z", owner->entity->getComponent <Rigidbody3d>().freezePosZ);

	owner->entity->getComponent <Rigidbody3d>().freezePosX = posX;
	owner->entity->getComponent <Rigidbody3d>().freezePosY = posY;
	owner->entity->getComponent <Rigidbody3d>().freezePosZ = posZ;
	ImGui::PopID();
	ImGui::NewLine();

	ImGui::SameLine();
	ImGui::PushID("FRRot");
	ImGui::Text("Freeze Rotation");
	ImGui::SameLine();
	bool rotX = EditorGUI::Toggle("X", owner->entity->getComponent <Rigidbody3d>().freezeRotX);
	ImGui::SameLine();
	bool rotY = EditorGUI::Toggle("Y", owner->entity->getComponent <Rigidbody3d>().freezeRotY);
	ImGui::SameLine();
	bool rotZ = EditorGUI::Toggle("Z", owner->entity->getComponent <Rigidbody3d>().freezeRotZ);

	owner->entity->getComponent <Rigidbody3d>().freezeRotX = rotX;
	owner->entity->getComponent <Rigidbody3d>().freezeRotY = rotY;
	owner->entity->getComponent <Rigidbody3d>().freezeRotZ = rotZ;
	ImGui::PopID();
	ImGui::NewLine();
}