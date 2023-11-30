#include "CTileMap.h"
#include "CSprite.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;


void CTileMap::start() {

}

void CTileMap::draw(Entity* owner) {
    ImGui::Button("Tile Map", ImVec2(ImGui::GetContentRegionAvail().x, 20));
    ImGui::Spacing();
    

    if (ImGui::TreeNode ("Tile Sprites")) {
        for (int i = 0; i < owner->getComponent<TileMapComponent>().TileSprites.size(); i++) {
            ImGui::PushID(i);
            owner->getComponent<TileMapComponent>().TileSprites[i] = EditorGUI::InputText ("Tile", owner->getComponent<TileMapComponent>().TileSprites[i]);
            
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

                        owner->getComponent<TileMapComponent>().TileSprites[i] = convertedPath;
                    }
                }


                ImGui::EndDragDropTarget();
            }
            ImGui::PopID();
        }

        ImGui::TreePop();
    }

    if (ImGui::Button("Add New Sprite", ImVec2(ImGui::GetWindowSize().x - 20, 20))) {
        owner->getComponent<TileMapComponent>().TileSprites.push_back("");
    }

    ImGui::Spacing();
    if (ImGui::Button ("Open Editor", ImVec2 (ImGui::GetWindowSize().x - 20, 20))) {
        UIManager::instance->tileMapUI->isOpen = true;
        UIManager::instance->tileMapUI->componentSelect = &owner->getComponent<TileMapComponent>();
        UIManager::instance->tileMapUI->ReSetup();

        for (int i = 0; i < UIManager::instance->tileMapUI->Images.size(); i++) {
            glDeleteTextures(1, &UIManager::instance->tileMapUI->Images[i]);
        }

        UIManager::instance->tileMapUI->Images.clear();

        for (int i = 0; i < owner->getComponent<TileMapComponent>().TileSprites.size(); i++) {
            UIManager::instance->tileMapUI->Images.push_back (UIManager::instance->tileMapUI->LoadTexture(owner->getComponent<TileMapComponent>().TileSprites[i]));
        }

        std::cout << "Tile Editor Open" << std::endl;
    }
}