#ifndef CAMERA2D_H
#define CAMERA2D_H
#include "../../RequireLibs.h"
#include "../../Graphics/StartEngineGraphics.h";
#include "../../Graphics/AppSettings.h"
#include "../InputSystem/InputSystem.h"

using namespace std;

class Camera {
public:
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    float zoom = 1;

    void start() {
        projection = glm::ortho(-static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, -static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, -1000.0f, 1000.0f);
    }

    void update() {
        projection = glm::ortho(-static_cast<float>(AppSettings::instance->ScreenWidth) / 
                    2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * 
                    zoom, -static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * 
                    zoom, static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * 
                    zoom, -1000.0f, 1000.0f);


        view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    }

    glm::mat4 GetProjectionMatrix() {
        return projection;
    }

    glm::mat4 GetView() {
        return view;
    }
};
#endif