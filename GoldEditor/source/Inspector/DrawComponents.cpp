#include "DrawComponents.h"
#include "../UI/UIManager.h"
#include "InspectorComponents.h"

InspectorComponents* components = new InspectorComponents();

void DrawComponents::start() {
	CAudio* audio = new CAudio();
	componentsDraw.push_back (audio);
}

void DrawComponents::update() {
	if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
		components->update (UIManager::instance->inspectorui->ObjectSelectToInspector);
	}

	ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
	ImVec2 buttonSize(contentRegionAvailable.x, 20);


	ImGui::PushID(9815);
	ImGui::Spacing ();
	ImGui::Separator();
 	if (ImGui::Button("Add Component", buttonSize)) {
		UIManager::instance->inspectorui->ObjectSelectToInspector->addComponent<AudioSource>();
	}

	//ImGui::Begin("Components", AddComponentOpen);

	//ImGui::End();
	ImGui::PopID();
}