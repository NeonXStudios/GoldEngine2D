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
        glm::vec2 initialMousePos;  // Posición del mouse cuando comenzó el arrastre
        glm::vec2 initialObjectPos; // Posición inicial del objeto cuando comenzó el arrastre

        if (ImGui::IsWindowHovered()) {
            for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
                Entity* objD = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];
                glm::vec3& obj = objD->getComponent<SpriteComponent>().ObjectPosition;
                float objWidth = objD->getComponent<SpriteComponent>().Scale.x * objD->getComponent<SpriteComponent>().GlobalScale;
                float objHeight = objD->getComponent<SpriteComponent>().Scale.y * objD->getComponent<SpriteComponent>().GlobalScale;

                // Obtén la rotación en radianes desde Box2D
                float radians = objD->getComponent<SpriteComponent>().rotationAngle * (b2_pi / 180.0f);

                // Aplica la rotación inversa al punto del mundo
                glm::vec2 localPoint = RotatePoint(WorldPoint, obj, radians);

                // Calcula las coordenadas de la caja delimitadora del objeto rotado
                glm::vec2 rotatedBoxMin(obj.x - objWidth * 0.5f, obj.y - objHeight * 0.5f);
                glm::vec2 rotatedBoxMax(obj.x + objWidth * 0.5f, obj.y + objHeight * 0.5f);
                glm::vec2 dragOffset;


                // Comprueba si el punto rotado está dentro de la caja delimitadora rotada
                if (localPoint.x >= rotatedBoxMin.x && localPoint.x <= rotatedBoxMax.x &&
                    localPoint.y >= rotatedBoxMin.y && localPoint.y <= rotatedBoxMax.y) {

                    if (ImGui::IsMouseClicked(0)) {
                        UIManager::instance->inspectorui->SelectEntity(objD);
                        ObjectSelect = true;

                        UIManager::instance->hierarhcyui->SelectInHierarchy = false;
                        std::cout << "Clicked object" << std::endl;
                        break;
                    }
                }
                else {
                    if (ImGui::IsMouseClicked (0)) {
                        UIManager::instance->inspectorui->ObjectSelectToInspector = nullptr;
                    }
                }

                
                if (ImGui::IsMouseDragging (0) && ImGui::IsMouseDown(0) && UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
                    UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.x = WorldPoint.x;
                    UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.y = WorldPoint.y;
                    isdragging = true;
                }

                if (!ImGui::IsMouseDragging (0)) {
                    isdragging = false;
                }
            }
        }        
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


    glm::vec2 SceneUI::RotatePoint(const glm::vec2& point, const glm::vec2& center, float angle) {
        glm::vec2 rotatedPoint;
        float cosTheta = cos(angle);
        float sinTheta = sin(angle);

        rotatedPoint.x = center.x + (point.x - center.x) * cosTheta - (point.y - center.y) * sinTheta;
        rotatedPoint.y = center.y + (point.x - center.x) * sinTheta + (point.y - center.y) * cosTheta;

        return rotatedPoint;
    }
