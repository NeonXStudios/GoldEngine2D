#include "CanvasUI.h"
#include "../UIManager.h"

void CanvasUI::start() {
  
    //glGenFramebuffers(1, &framebuffer);
}

void CanvasUI::draw() {
		ImGui::Begin("UI Tools", &isOpen);
		if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
			if (UIManager::instance->inspectorui->ObjectSelectToInspector->hasComponent<Canvas>()) {
				if (ImGui::Button("Button", ImVec2(ImGui::GetWindowSize().x, 20))) {
					UIButton* buttonNew = new UIButton();
					buttonNew->start();
					UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<Canvas>().Data.push_back (buttonNew);
				}

				if (ImGui::Button("Text", ImVec2(ImGui::GetWindowSize().x, 20))) {

				}

				if (ImGui::Button("Slider", ImVec2(ImGui::GetWindowSize().x, 20))) {

				}

				if (ImGui::Button("Input Text", ImVec2(ImGui::GetWindowSize().x, 20))) {

				}
			}
			else {
				ImGui::Text("CANVAS NOT FOUND");

			}
		}
		else {
			ImGui::Text ("YOU NEED SELECT A OBJECT");
		}
		ImGui::End();
}

void CanvasUI::update() {

}

void CanvasUI::lateupdate() {

}

void CanvasUI::fixupdate() {

}