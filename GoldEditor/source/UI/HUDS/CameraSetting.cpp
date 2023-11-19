#include "CameraSetting.h"
#include "../EditorUI/EditorGUI.h"
#include "../../Editor/GoldEditor.h"

void CameraSetting::start() {

}

void CameraSetting::draw() {
	if (isOpen) {
		ImGui::Begin ("Camera Setting");
		ImGui::Text ("Camera Mode");
		if (ImGui::Button("Ortho")) {
			SceneManager::GetSceneManager()->OpenScene->worldCamera->proj = Camera::Projection::Orthographic;
		}

		if (ImGui::Button("Perspective")) {
			SceneManager::GetSceneManager()->OpenScene->worldCamera->proj = Camera::Projection::Perspective;
		}
		ImGui::Separator();

		GoldEditor::editor->cameraSpeed = EditorGUI::Float("Speed", GoldEditor::editor->cameraSpeed);
		SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom = EditorGUI::Slider("Fov", SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, 0, 10);
		
		if (ImGui::Button("Close")) {
			isOpen = false;
		}
		ImGui::End();
	}
}

void CameraSetting::update() {

}

void CameraSetting::lateupdate() {

}

void CameraSetting::fixupdate() {

}