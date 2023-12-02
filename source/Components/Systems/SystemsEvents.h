#pragma once
#include "../../RequireLibs.h"
#include "../../Graphics/AppSettings.h"
#include "../../Graphics/StartEngineGraphics.h"
#include "../SceneManager/SceneManager.h"
#include <glm/glm.hpp>

using namespace glm;

namespace RenderSystem {
    class RenderSystem
    {
    public:
        static glm::vec2 ScreenToViewPort(glm::vec2 ViewportRenderPosition, glm::vec2 WindowSize) {
            double x, y;
            glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

            Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;

            double windowMousePosX = x - ViewportRenderPosition.x;
            double windowMousePosY = y - ViewportRenderPosition.y;

            double NormalMousePosX = (windowMousePosX / WindowSize.x);
            double NormalMousePosY = (-windowMousePosY / WindowSize.y);


            // CALCULAR CENTRO DE LA TEXTURA CON EL MOUSE (0, 0)
            double centeredMousePosX = ((NormalMousePosX * 2.0f - 1.0f) * (AppSettings::RenderWidth / 2) * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom);
            double centeredMousePosY = ((NormalMousePosY * 2.0f + 1.0f) * (AppSettings::RenderHeight / 2) * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom);


            double WorldPointX = centeredMousePosX + cam->cameraPosition.x;
            double WorldPointY = centeredMousePosY + cam->cameraPosition.y;


            std::cout << "Mouse X: " << WorldPointX << "Camera Pos X: " << cam->cameraPosition.x << std::endl;
            std::cout << "Mouse Y: " << WorldPointY << "Camera Pos Y: " << cam->cameraPosition.y << std::endl;


            return glm::vec2(WorldPointX, WorldPointY);
        }

        static glm::vec2 MouseToViewPortPosition (glm::vec2 ViewportRenderPosition, glm::vec2 WindowSize) {
            double x, y;
            glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

            double windowMousePosX = x - ViewportRenderPosition.x;
            double windowMousePosY = y - ViewportRenderPosition.y;

            double NormalMousePosX = windowMousePosX;
            double NormalMousePosY = windowMousePosY;

            // CALCULAR CENTRO DE LA TEXTURA CON EL MOUSE (0, 0)
            double centeredMousePosX = (NormalMousePosX * 2.0f - 1.0f) * (AppSettings::RenderWidth) * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom;
            double centeredMousePosY = (NormalMousePosY * 2.0f + 1.0f) * (AppSettings::RenderHeight) * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom;

            Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;

            double WorldPointX = centeredMousePosX + cam->cameraPosition.x;
            double WorldPointY = centeredMousePosY + cam->cameraPosition.y;


            return glm::vec2(NormalMousePosX, NormalMousePosY);
        }
    };
}


namespace InputSystem {
    class InputSystem
    {
    public:

        static bool GetKey        (int key)
        {
            return glfwGetKey(StartEngineGraphics::window, key) == GLFW_PRESS;
        };

        static bool GetKeyUp    (int key)
        {
            return glfwGetKey(StartEngineGraphics::window, key) == GLFW_RELEASE;
        };



        static vec2 GetGlobalMousePosition() {
            double y, x;
            glfwGetCursorPos(StartEngineGraphics::window, &y, &x);

            return vec2(x, y);
        }

        static vec2 GetMousePositionInViewPort(glm::vec2 ViewportRenderPosition, glm::vec2 WindowSize, glm::vec2 ScreenSize) {
            double x, y;
            glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

            double windowMousePosX = x - ViewportRenderPosition.x;
            double windowMousePosY = y - ViewportRenderPosition.y;

            double NormalMousePosX = windowMousePosX / WindowSize.x;
            double NormalMousePosY = -windowMousePosY / WindowSize.y;

            return vec2(0, 0);
        }
    };
}