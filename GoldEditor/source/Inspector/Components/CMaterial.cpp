#include "CMaterial.h"

void CMaterial::start() {

}

void CMaterial::draw(Entity* owner) {
    ImGui::Button("Material", ImVec2(ImGui::GetContentRegionAvail().x, 20));
    ImGui::Spacing();

    owner->getComponent<MaterialComponent>().VertexPath   = EditorGUI::InputText ("Vertex Shader", owner->getComponent<MaterialComponent>().VertexPath);
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_PATH", target_flags))
        {
            const char* receivedString = static_cast<const char*>(payload->Data);

            if (ImGui::IsMouseReleased(0)) {
                std::string convertedPath = AComponent::RemoveDir(receivedString);
                owner->getComponent<MaterialComponent>().VertexPath = convertedPath;



                std::cout << "Convertido: " << convertedPath << std::endl;
                owner->getComponent<MaterialComponent>().RecompileShader();
            }
        }


        ImGui::EndDragDropTarget();
    }
    
    owner->getComponent<MaterialComponent>().FragmentPath = EditorGUI::InputText ("Fragment Shader", owner->getComponent<MaterialComponent>().FragmentPath);
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_PATH", target_flags))
        {
            const char* receivedString = static_cast<const char*>(payload->Data);

            if (ImGui::IsMouseReleased(0)) {
                std::string convertedPath = AComponent::RemoveDir(receivedString);
                owner->getComponent<MaterialComponent>().FragmentPath = convertedPath;



                std::cout << "Convertido: " << convertedPath << std::endl;
                owner->getComponent<MaterialComponent>().RecompileShader();
            }
        }


        ImGui::EndDragDropTarget();
    }
}