#include "TileMapUI.h"


void TileMapUI::ReSetup() {

}

void TileMapUI::start() {

}

void TileMapUI::draw() {
	if (isOpen) {
		if (ImGui::Begin("Tile Editor", &isOpen)) {
			ImGui::SetCursorPos (ImVec2 (ImGui::GetWindowSize().x / 2, 0));
			ImGui::Text ("Tile Map Editor V1");
            float cellSize = 50.0f;

            // Número de columnas en el grid
            int numColumns = 5;

            for (int i = 0; i < 6; ++i) {
                // Calcula la posición de cada celda en el grid
                float x = (i % numColumns) * cellSize;
                float y = (i / numColumns) * cellSize;

                ImGui::SetCursorPos({ x + 20, y + 30 });

                // Dibuja algo en cada celda (puedes colocar una imagen aquí)
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