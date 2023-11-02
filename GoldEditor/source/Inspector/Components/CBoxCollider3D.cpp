//#include "CBoxCollider3D.h"
//#include "../../Gizmos/GDGizmos.h"
//#include "../../Editor/GoldEditor.h"
//
//void CBoxCollider3D::start() {
//
//}
//
//
//void CBoxCollider3D::draw(Entity* owner) {
//	ImGui::Button("Box Collider3D", ImVec2(ImGui::GetContentRegionAvail().x, 20));
//	ImGui::Spacing();
//
//	owner->getComponent <BoxCollider>().boxSize = EditorGUI::Vector3 ("Box Size", owner->getComponent <BoxCollider>().boxSize);
//	GoldEditor::editor->gizmos->DrawCube(owner->transform->Position, owner->getComponent <BoxCollider>().boxSize, glm::vec3(0, 1, 0));
//}