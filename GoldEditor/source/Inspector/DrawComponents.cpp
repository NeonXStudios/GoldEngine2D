#include "DrawComponents.h"
#include "../UI/UIManager.h"
#include "InspectorComponents.h"



//PROGRAMAR EL DIBUJADO DE COMPONENTES PARA EL MENU ADD COMPONENT
InspectorComponents* components = new InspectorComponents();

void DrawComponents::start() {


}

void DrawComponents::update() {
	if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
		components->update(UIManager::instance->inspectorui->ObjectSelectToInspector);
	}

	ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
	ImVec2 buttonSize(contentRegionAvailable.x, 20);


	ImGui::PushID(9815);
	ImGui::Spacing();
	ImGui::Separator();

	if (miniMenuOpen) {
		MousePosition = ImGui::GetMousePos();
		ImVec2 buttonPosMax = ImGui::GetItemRectMin();
		ImGui::SetNextWindowPos(ImVec2(buttonPosMax.x, buttonPosMax.y + 30));
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetContentRegionAvail().x - 10, 500));
	}


	if (miniMenuOpen && ImGui::Begin("Components", &miniMenuOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
		DrawButtons();
		ImGui::End();
	}

	if (ImGui::IsMouseReleased(0) && miniMenuOpen) {
		miniMenuOpen = false;
		std::cout << "Mouse soltado" << std::endl;
	}

	if (ImGui::Button("Add Component", buttonSize)) {
		miniMenuOpen = true;
	}


	ImGui::PopID();
}




void DrawComponents::DrawButtons() {
	Entity* objectOwner = UIManager::instance->inspectorui->ObjectSelectToInspector;
	ComponentList::createNewComponent <AudioSource>			("Audio Source", objectOwner);
	ComponentList::createNewComponent <RigidBody>			("RigidBody", objectOwner);
	ComponentList::createNewComponent <ScriptCompiler>		("Gold Behaviour", objectOwner);
}