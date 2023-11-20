#include "CScript.h"
#include "../../UI/UIManager.h"
#include "../../Editor/GoldEditor.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;


void CScript::start() {

}


void CScript::draw (Entity* owner) {
    ImGui::Button("Gold Behaviour", ImVec2(ImGui::GetContentRegionAvail().x, 20));
    ImGui::Spacing();
    ImGui::PushID("ScriptDROP");
	owner->getComponent<ScriptCompiler>().pathScript = EditorGUI::InputText ("Script Path", owner->getComponent<ScriptCompiler>().pathScript);
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SRSCRIPT_PATH", target_flags))
        {
            if (ImGui::IsMouseReleased(0)) {
                const char* receivedString = static_cast<const char*>(payload->Data);

                std::string convertedPath = AComponent::RemoveDir(receivedString);

                std::cout << "String recibido: " << receivedString << std::endl;
                owner->getComponent<ScriptCompiler>().pathScript = convertedPath;
            }

        }


        ImGui::EndDragDropTarget();
    }
    ImGui::PopID();

	if (EditorGUI::Button("Open script", vec2(100, 30))) {
		if (editor == nullptr) {
			UIManager::instance->createScriptEditor (owner);
		}
	}
    ImGui::SameLine();
	if (EditorGUI::Button("Open VSC", vec2(100, 30))) {
        string path = owner->getComponent <ScriptCompiler>().pathScript;
        const char* fileName = path.c_str();

        const char* command = "code";
        const char* arguments = fileName;

        char fullCommand[100]; 
        snprintf(fullCommand, sizeof(fullCommand), "%s %s", command, arguments);

        int result = system(fullCommand);

        if (result == 0) {
            printf("Archivo abierto exitosamente con VSCode.\n");
        }
        else {
            printf("Error al abrir el archivo con VSCode.\n");
        }
	}

	if (editor != nullptr) {
		editor->update();
	}
}