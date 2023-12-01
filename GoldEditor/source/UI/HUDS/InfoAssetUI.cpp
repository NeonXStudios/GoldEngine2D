#include "InfoAssetUI.h"
#include "../UIManager.h"

void InfoAssetUI::start() {

}

void InfoAssetUI::update() {

}

void InfoAssetUI::lateupdate() {

}

void InfoAssetUI::fixupdate() {

}

void InfoAssetUI::draw() {
	if (openUI) {
		if (ImGui::Begin ("Info Asset", &openUI)) {
            string TitleF = "ASSET PATH: " + assetPath;

			ImGui::Text  (TitleF.c_str());
			ImGui::Image ((void*)(intptr_t)SelectUIIMG, ImVec2 (128, 128));

            if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr && UIManager::instance->inspectorui->ObjectSelectToInspector->hasComponent<TileMapComponent>()) {
                if (ImGui::Button ("Send To Select Tile Map")) {
                    UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<TileMapComponent>().TileSprites.push_back (assetPath);
                }
            }

            ImGui::End();
		}
    }
    //else {
    //    if (SelectUIIMG != -1) {
    //        glDeleteBuffers(1, &SelectUIIMG);
    //        std::cout << "Liberando memoria del buffer con la ventana cerrada" << std::endl;
    //    }
    //}
}

void InfoAssetUI::LoadIMG(string pathIMG) {

    if (SelectUIIMG != -1) {
        glDeleteBuffers(1, &SelectUIIMG);
        std::cout << "Liberando memoria del buffer " << pathIMG << std::endl;
    }

    std::cout << "La nueva ruta de la textura es " << pathIMG << std::endl;
    int width, height, nrChannels;
    string newPath = FileSystem::GetAsset(pathIMG);
    std::cout << "NUEVA RUTA:" << newPath << std::endl;

    unsigned char* data = stbi_load(newPath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, SelectUIIMG);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}