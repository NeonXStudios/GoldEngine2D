#include "../UIDrawer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int framebuffer;
unsigned int texture;
int textureWidth, textureHeight;
ImVec2 imagePosition;

class SceneUI : public UIDrawer {

public:
    unsigned int framebuffer;
    unsigned int texture;
    ImVec2 imageSizeSCENE;
    ImVec2 TextureSize;

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

    bool isMouseInsideRect(double xpos, double ypos, double rectX, double rectY, double rectWidth, double rectHeight) {
        return (xpos >= rectX && xpos <= rectX + rectWidth &&
            ypos >= rectY && ypos <= rectY + rectHeight);
    }

	void draw() override {

        ImVec2 windowSize = ImVec2(1920, 1080);

        // Dibujamos la imagen en la ventana de ImGui
        ImGui::SetNextWindowSize(windowSize);
        ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        glm::vec3 cameraPosition = SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition;



        // Obtenemos el tamaño de la ventana de ImGui después de que se apliquen las restricciones de tamaño
        ImVec2 actualWindowSize = ImGui::GetWindowSize();
        float scaleFactor = std::min(actualWindowSize.x / windowSize.x, actualWindowSize.y / windowSize.y);
        imageSizeSCENE = ImVec2(1920.0f * scaleFactor, 1080.0f * scaleFactor);

        // Calculamos el tamaño final sin escalar
        ImVec2 finalImageSize = ImVec2(1920.0f, 1080.0f);

        // Calculamos la posición para centrar la imagen en la ventana
        imagePosition = ImVec2((actualWindowSize.x - imageSizeSCENE.x) * 0.5f, (actualWindowSize.y - imageSizeSCENE.y) * 0.5f);

        ImGui::SetCursorPos(imagePosition);

        // Invertimos las coordenadas de textura en el eje Y antes de mostrar la imagen
        ImGui::Image((void*)(intptr_t)texture, imageSizeSCENE, ImVec2(0, 1), ImVec2(1, 0));
        glBindTexture(GL_TEXTURE_2D, (intptr_t)texture);

        // Obtener el ancho de la textura
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);

        // Obtener el alto de la textura
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

        TextureSize.x = textureWidth;
        TextureSize.y = textureHeight;
        // Después de obtener el tamaño de la textura, puedes usarlo como lo necesites
        //std::cout << "Tamaño de la textura: " << textureWidth << "x" << textureHeight << std::endl;

        imagePosition.x += ImGui::GetWindowPos().x;
        imagePosition.y += ImGui::GetWindowPos().y;


        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            double x, y;
            glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

            double windowMousePosX = x - imagePosition.x;
            double windowMousePosY = y - imagePosition.y;


            std::cout << "Texture Mouse PosX: " << windowMousePosX << " | Texture Mouse PosY: " << windowMousePosY << std::endl;
        }





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




/*


 if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            double x, y;
            glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

            double windowMousePosX = x - imagePosition.x;
            double windowMousePosY = y - imagePosition.y;

            std::cout << "Window Mouse PosX: " << windowMousePosX << " | Window Mouse PosY: " << windowMousePosY << std::endl;

            // Obtener el tamaño de la ventana de ImGui después de que se apliquen las restricciones de tamaño
            ImVec2 actualWindowSize = ImGui::GetWindowSize();
            float scaleFactor = std::min(actualWindowSize.x / windowSize.x, actualWindowSize.y / windowSize.y);
            ImVec2 imageSize = ImVec2(1920.0f * scaleFactor, 1080.0f * scaleFactor);

            // Coordenadas del centro de la textura
            float textureCenterX = imageSize.x * 0.5f;
            float textureCenterY = imageSize.y * 0.5f;

            // Ajustar las coordenadas del mouse para que estén en relación con el centro de la textura
            float textureMousePosX = windowMousePosX - textureCenterX;
            float textureMousePosY = windowMousePosY - textureCenterY;

            // Ajustar las coordenadas del objeto para que estén centradas en la textura y considerar la distancia de la cámara
            float objWidth = 25;
            float objHeight = 25;

            // Verificar si el clic se realizó dentro de alguno de los objetos
            for (const auto& objD : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
                glm::vec3& obj = objD->getComponent<SpriteComponent>().cubePosition;

                // Convertir las coordenadas del objeto al espacio de la cámara
                glm::vec4 objPosCamSpace = glm::vec4(obj, 1.0f) * SceneManager::GetSceneManager()->OpenScene->worldCamera->GetView();

                // Normalizar las coordenadas para considerar la distancia de la cámara
                float normX = objPosCamSpace.x / objPosCamSpace.w;
                float normY = objPosCamSpace.y / objPosCamSpace.w;

                // Ajustar las coordenadas del objeto para que estén centradas en la textura
                float objX = normX - objWidth * 0.5f;
                float objY = -normY - objHeight * 0.5f;

                if (textureMousePosX >= objX && textureMousePosX <= objX + objWidth &&
                    textureMousePosY >= objY && textureMousePosY <= objY + objHeight) {
                    // Hacer clic en el objeto (realizar la acción deseada)
                    std::cout << "Objeto cliqueado: " << objD->ObjectTag << std::endl;
                    // Agregar aquí la lógica para la acción deseada para el objeto clickeado
                    break; // Si solo quieres detectar un objeto clickeado, puedes agregar break aquí
                }
            }
        }
        
        
        */