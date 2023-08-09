#pragma once
#include <iostream>
#include <filesystem>
#include <string.h>

#include "../UIDrawer.h"
#include <stb_image.h>

namespace fs = std::filesystem;
using namespace std;

class AssetsUI : public UIDrawer {

public:
    GLuint texture_id;
    unsigned char* image_data;
    int width, height, channels;
    bool isDragging = false;


    void start() override {
        image_data = stbi_load("game/engine/ICONS/folderpath.png", &width, &height, &channels, STBI_rgb_alpha);
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        std::cout << "TEXTURE STARTED FOR PATHS" << std::endl;
    }

    void draw() override {
        ImGui::Begin ("Assets");

        std::string path_to_read = "game/assets/";

        try {
            for (const auto& entry : fs::directory_iterator(path_to_read)) {
                if (fs::is_directory(entry)) {
                    std::string namePath = entry.path().filename().string();
                    ImGui::PushID (namePath.c_str());
                    ImVec4 transparentColor(0.0f, 0.0f, 0.0f, 0.0f); // RGBA (negro completamente transparente)
                    ImGui::PushStyleColor(ImGuiCol_Button, transparentColor);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, transparentColor);
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, transparentColor);
                    if (ImGui::ImageButton((void*)(intptr_t)texture_id, ImVec2(50, 50))) {
                        ImGui::OpenPopup("Button Clicked");
                    }


                    ImGui::Text (namePath.c_str());
                    ImGui::PopID();
                    ImGui::PopStyleColor(3);
                }
            }
        }
        catch (const fs::filesystem_error& ex) {
            std::cerr << "Error al acceder a la ruta: " << ex.what() << std::endl;
        }  

        ImGui::End();
    }


    void update() override {

    }

    void lateupdate() override {

    }

    void fixupdate() override {

    }
};