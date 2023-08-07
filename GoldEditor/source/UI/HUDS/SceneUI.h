#pragma once
#include "../UIDrawer.h"
#include "../Editor/GoldEditor.h"
#include "../../source/Components/Systems/SystemsEvents.h"

unsigned int framebuffer;
unsigned int texture;
int textureWidth, textureHeight;
ImVec2 imagePosition;

class SceneUI : public UIDrawer {

public:
    unsigned int framebuffer;
    unsigned int texture;
    ImVec2 imageSizeSCENE;
    double textureMousePosX = 0;
    double textureMousePosY = 0;

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


        for (Entity* objD : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
            glm::vec3& obj = objD->getComponent<SpriteComponent>().cubePosition;

            // Convertir las coordenadas del objeto al espacio de la cámara
            float objWidth = 25;
            float objHeight = 25;

            // Ajustar las coordenadas del objeto para que estén centradas en el espacio de la cámaraf
            float objX = (obj.x - objWidth   * 0.5f);
            float objY = (-obj.y - objHeight * 0.5f);

            if (WorldPoint.x >= objX && WorldPoint.x <= objX + objWidth &&
                WorldPoint.y >= objY && WorldPoint.y <= objY + objHeight) {
                // Hacer clic en el objeto (realizar la acción deseada)
                std::cout << "Objeto cliqueado: " << objD->ObjectName << std::endl;
                std::cout << "X: " << objX <<  " | Y: " << objY << std::endl;
                // Agregar aquí la lógica para la acción deseada para el objeto clickeado
                break; // Si solo quieres detectar un objeto clickeado, puedes agregar break aquí
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



/* PICKING WORKING WITHOUT CAMERA POSITION


 double x, y;
        glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

        double windowMousePosX = x - imagePosition.x;
        double windowMousePosY = y - imagePosition.y;

        // Obtener el ancho y alto de la imagen o textura
        double imageWidth = imageSizeSCENE.x; // Ancho de la imagen
        double imageHeight = imageSizeSCENE.y; // Alto de la imagen


        // Ajustar la posición para que el centro sea el punto de origen
        double centeredMousePosX = windowMousePosX - (imageWidth * 0.5);
        double centeredMousePosY = windowMousePosY - (imageHeight * 0.5);

        // Obtener el tamaño actual de la ventana
        ImVec2 actualWindowSize2 = ImGui::GetWindowSize();

        // Obtener el factor de escala para convertir las coordenadas del mouse a las coordenadas en el espacio de la textura
        float scaleFactor2 = std::min(actualWindowSize2.x / windowSize.x, actualWindowSize2.y / windowSize.y);
        textureMousePosX = centeredMousePosX / scaleFactor2;
        textureMousePosY = centeredMousePosY / scaleFactor2;



        //if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        //
        //}

        ImGui::Begin("Picking Position");
        ImGui::Text("Mouse X: %f", textureMousePosX);
        ImGui::Text("Mouse Y: %f", textureMousePosY);
        ImGui::End();

        ImGui::Begin("OBJECTS IN SCENE");

        for (Entity* objD : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
            glm::vec3& obj = objD->getComponent<SpriteComponent>().cubePosition;

            // Convertir las coordenadas del objeto al espacio de la cámara
            glm::vec3 objPosCamSpace = obj - SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition;

            float objWidth = 25;
            float objHeight = 25;

            // Ajustar las coordenadas del objeto para que estén centradas en el espacio de la cámara
            float objX = objPosCamSpace.x - objWidth * 0.5f;
            float objY = objPosCamSpace.y - objHeight * 0.5f;

            ImGui::Text("Object tag: %f", objD->ObjectTag.c_str());
            ImGui::Text("Pos x: : %f", objX);
            ImGui::Text("Pos y: : %f", objY);

            if (textureMousePosX >= objX && textureMousePosX <= objX + objWidth &&
                textureMousePosY >= objY && textureMousePosY <= objY + objHeight) {
                // Hacer clic en el objeto (realizar la acción deseada)
                std::cout << "Objeto cliqueado: " << objD->ObjectTag << std::endl;
                // Agregar aquí la lógica para la acción deseada para el objeto clickeado
                break; // Si solo quieres detectar un objeto clickeado, puedes agregar break aquí
            }
        }
        ImGui::End();


if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {

    }

*/