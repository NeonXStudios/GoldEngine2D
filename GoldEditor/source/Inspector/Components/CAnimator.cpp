#include "CAnimator.h"

CAnimator::CAnimator() {

}

void CAnimator::start() {

}

void CAnimator::draw(Entity* owner) {
	ImGui::Button("Animator", ImVec2(ImGui::GetContentRegionAvail().x, 20));
	ImGui::Spacing();

	owner->getComponent<Animator2D>().SelectState = EditorGUI::InputText ("Select State", owner->getComponent<Animator2D>().SelectState);
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::PushID("CAnimator2D");


	if (ImGui::TreeNode ("Animator States")) {
		for (int i = 0; i < owner->getComponent<Animator2D>().states.size(); i++) {

			ImGui::PushID (i);

			AnimationsStates* anims = owner->getComponent<Animator2D>().states[i];
			anims->StateName = EditorGUI::InputText("State Name:", anims->StateName.c_str());

			if (ImGui::TreeNode("State")) {
				for (int g = 0; g < anims->FramesPath.size(); g++) {
					ImGui::PushID (+g);
					string newPath = EditorGUI::InputText("Frame:", anims->FramesPath[g]);
					anims->FramesPath[g] = newPath;

					if (ImGui::BeginDragDropTarget())
					{
						ImGuiDragDropFlags target_flags = 0;
						target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
						target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


						if (ImGui::IsMouseReleased(0)) {
							if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTUREDA_PATH", target_flags))
							{
								const char* receivedString = static_cast<const char*>(payload->Data);


								std::string convertedPath = AComponent::RemoveDir(receivedString);
								newPath = convertedPath;


								anims->FramesPath[g] = newPath;
								std::cout << "Convertido: " << convertedPath << std::endl;
							}
						}


						ImGui::EndDragDropTarget();
					}
					ImGui::PopID();
				}

				if (ImGui::Button ("Add New Frame")) {
					anims->AddNewFrame("");
				}
				ImGui::TreePop();
			}

			ImGui::PopID();
		}
		ImGui::TreePop();
	}


	if (ImGui::Button ("Add New State", ImVec2(ImGui::GetContentRegionAvail().x, 20))) {
		owner->getComponent<Animator2D>().states.push_back (new AnimationsStates());
	}

	if (ImGui::Button ("Rebuild Animator", ImVec2(ImGui::GetContentRegionAvail().x, 20))) {
		owner->getComponent<Animator2D>().RebuildAnimator();
	}

	ImGui::PopID();
}