#include "TileMapUI.h"
#include "../../UI/UIManager.h"
#include "../../Editor/GoldEditor.h"

void TileMapUI::ReSetup() {

}

void TileMapUI::start() {

}

void TileMapUI::draw() {
	if (isOpen) {
        if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && ImGui::IsMouseClicked(0) && instanceEntity == nullptr) {
            glm::vec2 WorldPoint = RenderSystem::RenderSystem::ScreenToViewPort(glm::vec2(UIManager::instance->sceneui->imagePosition.x, UIManager::instance->sceneui->imagePosition.y), glm::vec2(UIManager::instance->sceneui->imageSizeSCENE.x, UIManager::instance->sceneui->imageSizeSCENE.y));

            CastData* data = new CastData();
            ObjectCaster* caster = new ObjectCaster();
            if (caster->MouseCast(WorldPoint, data)) {
                SceneManager::GetSceneManager()->Destroy(data->object);
                UIManager::instance->inspectorui->ObjectSelectToInspector = nullptr;
            }
        }


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

            ImGui::Spacing();
            componentSelect->SizeTile = EditorGUI::Vector2 ("Tile Size: ", componentSelect->SizeTile);
            componentSelect->SnapMultiply = EditorGUI::Float ("Snap Size", componentSelect->SnapMultiply);

            
            if (EditionModeActive && GoldEditor::editor->activeMouse && !ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
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

                            if (!string(TileSelect).empty()) {
                                instanceEntity->getComponent<SpriteComponent>().TexturePath = TileSelect;
                                instanceEntity->getComponent<SpriteComponent>().LoadTexture();
                            }

                            instanceEntity = nullptr;
                        }
                    }
                }
            }           


            float cellSize = 32.0f;
            int numColumns = 5;
            float buttonSpacingX = 10.0f;
            float buttonSpacingY = 15.0f;


            for (int i = 0; i < Images.size(); ++i) {
                float x = (i % numColumns) * (cellSize + buttonSpacingX);
                float y = (i / numColumns) * (cellSize + buttonSpacingY);

                ImGui::SetCursorPos({ x + 20, y + 100 });

                if (ImGui::ImageButton((ImTextureID)(intptr_t)Images[i], ImVec2(cellSize, cellSize))) {
                    TileSelect = componentSelect->TileSprites[i];
                }
            }

            if (ImGui::Button("Reload TileMap")) {

                for (int i = 0; i < Images.size(); i++) {
                    glDeleteTextures(1, &Images[i]);
                }

                Images.clear();

                for (int i = 0; i < componentSelect->TileSprites.size(); i++) {
                    Images.push_back(LoadTexture(componentSelect->TileSprites[i]));
                }
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

GLuint TileMapUI::LoadTexture (string TexturePath) {
    std::cout << "La nueva ruta de la textura es " << TexturePath << std::endl;
    int width, height, nrChannels;
    string newPath = FileSystem::GetAsset(TexturePath);
    std::cout << "NUEVA RUTA:" << newPath << std::endl;

    GLuint texture;
    glGenTextures(1, &texture);

    unsigned char* data = stbi_load(newPath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    return texture;
}
