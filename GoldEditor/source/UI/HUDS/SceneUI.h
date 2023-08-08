#pragma once
#include "../UIDrawer.h"

class SceneUI : public UIDrawer {
public:
    unsigned int framebuffer;
    unsigned int texture;
    ImVec2 imageSizeSCENE;
    double textureMousePosX = 0;
    double textureMousePosY = 0;
    int textureWidth, textureHeight;
    ImVec2 imagePosition;


    void start() override;

    void draw() override;

    void update() override;

    void lateupdate() override;

    void fixupdate() override;
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