#include "../UIDrawer.h"
#include <stb_image.h>

class AssetsUI : public UIDrawer {

public:
    GLuint texture_id;
    unsigned char* image_data;
    int width, height, channels;

    void start() override {
        image_data = stbi_load("assets/ICONS/folderpath.png", &width, &height, &channels, STBI_rgb_alpha);
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        std::cout << "TEXTURE STARTED FOR PATHS" << std::endl;
    }

    void draw() override {
        ImGui::Begin ("Assets");

        if (ImGui::ImageButton((void*)(intptr_t)texture_id, ImVec2(50, 50))) {
            ImGui::OpenPopup("Button Clicked");
        }

        // Centrar el texto debajo del botón
        ImGui::SameLine(ImGui::GetCursorPosX() + (50 - ImGui::CalcTextSize("Scripts").x) * 0.5f);
        ImGui::Text("Scripts");

        ImGui::End();
    }

    void update() override {

    }

    void lateupdate() override {

    }

    void fixupdate() override {

    }
};