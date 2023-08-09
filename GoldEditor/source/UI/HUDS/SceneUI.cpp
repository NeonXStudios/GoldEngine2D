#pragma once
#include "SceneUI.h"
#include "../UIManager.h"


    void SceneUI::start () {
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


    void SceneUI::draw() {
        ImVec2 windowSize = ImVec2(AppSettings::ScreenWidth, AppSettings::ScreenHeight);

        // Dibujamos la imagen en la ventana de ImGui
        ImGui::SetNextWindowSize(windowSize);
        ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        //RenderSizeWindow = ImGui::GetWindowSize();

        // Obtenemos el tamaño de la ventana de ImGui después de que se apliquen las restricciones de tamaño
        ImVec2 actualWindowSize = ImGui::GetWindowSize();
        float scaleFactor = std::min(actualWindowSize.x / windowSize.x, actualWindowSize.y / windowSize.y);
        imageSizeSCENE = ImVec2(AppSettings::ScreenWidth * scaleFactor, AppSettings::ScreenHeight * scaleFactor);


        // Calculamos la posición para centrar la imagen en la ventana
        imagePosition = ImVec2((actualWindowSize.x - imageSizeSCENE.x) * 0.5f, (actualWindowSize.y - imageSizeSCENE.y) * 0.5f);

        ImGui::SetCursorPos(imagePosition);

        int WindowXSize = imageSizeSCENE.x;
        int WindowYSize = imageSizeSCENE.y;
        imageSizeSCENE.x = WindowXSize;
        imageSizeSCENE.y = WindowYSize;

        // Invertimos las coordenadas de textura en el eje Y antes de mostrar la imagen
        ImGui::Image((void*)(intptr_t)texture, ImVec2(WindowXSize, WindowYSize), ImVec2(1, 1), ImVec2(0, 0));

        //std::cout << "Nuevo tamaño de la textura: " << imageSizeSCENE.x << "x" << imageSizeSCENE.y << std::endl;

        // Después de obtener el nuevo tamaño de la textura, puedes usarlo como lo necesites

        imagePosition.x += ImGui::GetWindowPos().x;
        imagePosition.y += ImGui::GetWindowPos().y;

        glm::vec2 WorldPoint = RenderSystem::RenderSystem::ScreenToViewPort (glm::vec2 (imagePosition.x, imagePosition.y), glm::vec2 (imageSizeSCENE.x, imageSizeSCENE.y));


        if (ImGui::IsMouseClicked (0)) {
            for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
                Entity* objD = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];
                    glm::vec3 & obj = objD->getComponent<SpriteComponent>().ObjectPosition;

                // Convertir las coordenadas del objeto al espacio de la cámara
                float objWidth  = objD->getComponent<SpriteComponent>().Scale.x  * objD->getComponent<SpriteComponent>().GlobalScale;
                float objHeight = objD->getComponent<SpriteComponent>().Scale.y  * objD->getComponent<SpriteComponent>().GlobalScale;

                // Ajustar las coordenadas del objeto para que estén centradas en el espacio de la cámaraf
                float objX = (obj.x - objWidth * 0.5f);
                float objY = (-obj.y - objHeight * 0.5f);

                if (WorldPoint.x >= objX && WorldPoint.x <= objX + objWidth && WorldPoint.y >= objY && WorldPoint.y <= objY + objHeight) {
                    UIManager::instance->inspectorui->SelectEntity (objD);
                    break;
                }
            }

        }



        /*
        ImGui::Begin("Picking Position");
        ImGui::Text("Mouse Window X: %f", InputSystem::GetMousePositionGlobal().x);
        ImGui::Text("Mouse Window Y: %f", InputSystem::GetMousePositionGlobal().y);
        ImGui::Spacing();
        ImGui::Text("Mouse Scene X: %f", InputSystem::GetMousePositionViewPort(glm::vec2(imagePosition.x, imagePosition.y), glm::vec2(imageSizeSCENE.x, imageSizeSCENE.y)).x);
        ImGui::Text("Mouse Scene Y: %f", InputSystem::GetMousePositionViewPort(glm::vec2(imagePosition.x, imagePosition.y), glm::vec2(imageSizeSCENE.x, imageSizeSCENE.y)).y);
        ImGui::Spacing();
        ImGui::Text("Render Size X: %f", imageSizeSCENE.x);
        ImGui::Text("Render Size Y: %f", imageSizeSCENE.y);
        ImGui::End();

        */

        ImGui::End();
    }

    void SceneUI::update() {

    }

    void SceneUI::lateupdate() {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    }


    void SceneUI::fixupdate() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Copiar el contenido del framebuffer en la textura
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
        glBindTexture(GL_TEXTURE_2D, texture);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    }
