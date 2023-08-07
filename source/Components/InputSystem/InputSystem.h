#pragma once
#include "../../RequireLibs.h"
#include "../../Graphics/StartEngineGraphics.h"
#include "../../Graphics/AppSettings.h"
#include <iostream>

using namespace glm;


class InputSystem
{
public:

    static bool GetKey(int key)
    {
        return glfwGetKey(StartEngineGraphics::window, key) == GLFW_PRESS;
    };


    static vec2 GetGlobalMousePosition() {
        double y, x;
        glfwGetCursorPos (StartEngineGraphics::window, &y, &x);

        return vec2 (x, y);
    }

    static vec2 GetMousePositionInViewPort (glm::vec2 ViewportRenderPosition, glm::vec2 WindowSize, glm::vec2 ScreenSize) {
        double x, y;
        glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

        double windowMousePosX = x - ViewportRenderPosition.x;
        double windowMousePosY = y - ViewportRenderPosition.y;

        double NormalMousePosX = windowMousePosX / WindowSize.x;
        double NormalMousePosY = -windowMousePosY / WindowSize.y;

        //double centeredMousePosX = (NormalMousePosX * 2.0f - 1.0f) * (ScreenSize.x / 2) * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom;
        //double centeredMousePosY = (NormalMousePosY * 2.0f + 1.0f) * (ScreenSize.y / 2) * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom;

        //Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;

        //double WorldPointX = (centeredMousePosX + cam->cameraPosition.x);
        //double WorldPointY = (centeredMousePosY - cam->cameraPosition.y);


        return vec2 (0,0);
    }
};