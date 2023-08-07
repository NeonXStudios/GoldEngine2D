#pragma once
#include "../../RequireLibs.h"
#include "../../Graphics/AppSettings.h"
#include "../../Graphics/StartEngineGraphics.h"
#include "../SceneManager/SceneManager.h"

class RenderSystem
{
public:
	static glm::vec2 ScreenToViewPort (glm::vec2 ViewportRenderPosition, glm::vec2 WindowSize) {
        double x, y;
        glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

        double windowMousePosX = x - ViewportRenderPosition.x;
        double windowMousePosY = y - ViewportRenderPosition.y;

        double NormalMousePosX = windowMousePosX / WindowSize.x;
        double NormalMousePosY = -windowMousePosY / WindowSize.y;

        // CALCULAR CENTRO DE LA TEXTURA CON EL MOUSE (0, 0)
        double centeredMousePosX = (NormalMousePosX * 2.0f - 1.0f) * (AppSettings::ScreenWidth / 2) * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom;
        double centeredMousePosY = (NormalMousePosY * 2.0f + 1.0f) * (AppSettings::ScreenHeight / 2) * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom;

        Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;

        double WorldPointX = (centeredMousePosX + cam->cameraPosition.x);
        double WorldPointY = (centeredMousePosY - cam->cameraPosition.y);


        return glm::vec2 (WorldPointX, WorldPointY);
	}
};