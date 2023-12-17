#include "CCanvas.h"

void CCanvas::start() {

}

void CCanvas::draw(Entity* owner) {
	ImGui::Button("Canvas", ImVec2(ImGui::GetContentRegionAvail().x, 20));
	ImGui::Spacing();

	if (ImGui::Button ("Open Editor UI")) {
		UIManager::instance->canvasUI->isOpen = true;
	}
}