#include "CSkybox.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;


void CSkybox::start() {

}

void CSkybox::draw(Entity* owner) {
    ImGui::Button("Sprite", ImVec2(ImGui::GetContentRegionAvail().x, 20));
    ImGui::Spacing(); 
}