#include "TileMapUI.h"
#include "../../UI/UIManager.h"
#include "../../Editor/GoldEditor.h"

void TileMapUI::ReSetup() {

}

void TileMapUI::start() {

}

void TileMapUI::draw() {
	if (isOpen) {
		if (ImGui::Begin("Tile Editor", &isOpen)) {
            if (EditionModeActive) {
                if (ImGui::Button("Edition Mode (Active)")) {
                    EditionModeActive = false;
                }
            }
            else {
                if (ImGui::Button("Edition Mode")) {
                    EditionModeActive = true;
                }
            }

            componentSelect->SizeTile = EditorGUI::Vector2 ("Tile Size: ", componentSelect->SizeTile);
            componentSelect->SnapMultiply = EditorGUI::Float ("Snap Size", componentSelect->SnapMultiply);

            
            if (EditionModeActive && GoldEditor::editor->activeMouse) {
                if (instanceEntity == nullptr) {
                    if (ImGui::IsMouseClicked(0)) {
                        Entity* newSprite = SceneManager::GetSceneManager()->NewEntity();
                        instanceEntity = newSprite;
                    }

                }
                else {
                    if (instanceEntity != nullptr) {
                        glm::vec2 WorldPoint = RenderSystem::RenderSystem::ScreenToViewPort(glm::vec2(UIManager::instance->sceneui->imagePosition.x, UIManager::instance->sceneui->imagePosition.y), glm::vec2(UIManager::instance->sceneui->imageSizeSCENE.x, UIManager::instance->sceneui->imageSizeSCENE.y));
                        instanceEntity->transform->Position = glm::vec3(
                            (int)(WorldPoint.x / componentSelect->SnapMultiply) * componentSelect->SnapMultiply,
                            (int)(WorldPoint.y / componentSelect->SnapMultiply) * componentSelect->SnapMultiply,
                            0.0f);


                        instanceEntity->transform->Scale = glm::vec3 (componentSelect->SizeTile.x, componentSelect->SizeTile.y, 1);
                        
                        if (ImGui::IsMouseClicked(0)) {
                            instanceEntity = nullptr;
                        }
                    }
                }
            }

            


			ImGui::SetCursorPos (ImVec2 (ImGui::GetWindowSize().x / 2, 0));
			ImGui::Text ("Tile Map Editor V1");
            float cellSize = 50.0f;

            // Número de columnas en el grid
            int numColumns = 5;

            for (int i = 0; i < 6; ++i) {
                float x = (i % numColumns) * cellSize;
                float y = (i / numColumns) * cellSize;

                ImGui::SetCursorPos({ x + 20, y + 100 });

                ImGui::Button(("Cell " + std::to_string(i)).c_str(), ImVec2(cellSize, cellSize));
            }

			ImGui::End();
		}
	}
}

void TileMapUI::update() {
	
}

void TileMapUI::lateupdate() {

}

void TileMapUI::fixupdate() {

}