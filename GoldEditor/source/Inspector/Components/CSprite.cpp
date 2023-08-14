#include "CSprite.h"


void CSprite::start() {

}

void CSprite::draw (Entity* owner) {
	EditorGUI::Text("Sprite");

	string newPath = EditorGUI::InputText("File Path", owner->getComponent<SpriteComponent>().TexturePath);
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTUREDA_PATH", target_flags))
        {
            const char* receivedString = static_cast<const char*>(payload->Data);


            newPath = receivedString;
            owner->getComponent<SpriteComponent>().LoadTexture();
            std::cout << "String recibido: " << owner->getComponent<SpriteComponent>().TexturePath << std::endl;
        }


        ImGui::EndDragDropTarget();
    }

	if (owner->getComponent<SpriteComponent>().TexturePath != newPath) {
		owner->getComponent<SpriteComponent>().TexturePath = newPath;
		owner->getComponent<SpriteComponent>().LoadTexture();
	}
}