#include "../UIDrawer.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "../../source/Graphics/AppSettings.h"

class SceneUI : public UIDrawer {
    unsigned int framebuffer;
    unsigned int texture;

public:
	void start() override {
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer is not complete!" << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	void draw() override {
        
        ImVec2 windowSize = ImVec2(1920, 1080);

        // Dibujamos la imagen en la ventana de ImGui
        ImGui::SetNextWindowSize(windowSize);
        ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

        // Obtenemos el tamaño de la ventana de ImGui después de que se apliquen las restricciones de tamaño
        ImVec2 actualWindowSize = ImGui::GetWindowSize();
        float scaleFactor = std::min(actualWindowSize.x / windowSize.x, actualWindowSize.y / windowSize.y);
        ImVec2 imageSize = ImVec2(1920.0f * scaleFactor, 1080.0f * scaleFactor);

        // Calculamos la posición para centrar la imagen en la ventana
        ImVec2 imagePosition = ImVec2((actualWindowSize.x - imageSize.x) * 0.5f, (actualWindowSize.y - imageSize.y) * 0.5f);

        ImGui::SetCursorPos(imagePosition);

        // Invertimos las coordenadas de textura en el eje Y antes de mostrar la imagen
        ImGui::Image((void*)(intptr_t)texture, imageSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();


        ImGui::Begin ("ASSETS");
        ImGui::Button ("LAKAKA");
        ImGui::End();
        
	}

    void update() {

    }

    void lateupdate() {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    }


    void fixupdate() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Copiar el contenido del framebuffer en la textura
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
        glBindTexture(GL_TEXTURE_2D, texture);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    }
};