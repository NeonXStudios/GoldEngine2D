#include "CScript.h"
#include "../../UI/UIManager.h"


void CScript::start() {

}


void CScript::draw (Entity* owner) {
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


                std::cout << "String recibido: " << receivedString << std::endl;
                owner->getComponent<ScriptCompiler>().pathScript = receivedString;
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

	if (EditorGUI::Button("Open VSC", vec2(100, 30))) {
        string path = "game/assets/" + owner->getComponent <ScriptCompiler>().pathScript + ".sr";
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