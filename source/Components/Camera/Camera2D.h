#pragma once
#include "../../RequireLibs.h"
#include "../../Graphics/StartEngineGraphics.h";
#include "../../Graphics/AppSettings.h"

using namespace std;




class Camera {
public:
    enum Projection {
        Perspective,
        Orthographic
    };

    Projection proj = Projection::Orthographic;
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);  // Dirección hacia la que mira la cámara
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);      // Vector hacia arriba de la cámara
    float fov = 45.0f;  // Campo de visión en grados
    float zoom = 1;

    void start() {
        //projection = glm::ortho(-static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, -static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, -1000.0f, 1000.0f);
    }

    void update() {
        if (proj == Projection::Perspective) {
            float aspectRatio = static_cast<float>(AppSettings::instance->ScreenWidth) / static_cast<float>(AppSettings::instance->ScreenHeight);
            projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 1000.0f);

            // Asegurarse de normalizar la dirección de la cámara
            cameraFront = glm::normalize(cameraFront);

            // Calcular la nueva posición de la cámara
            glm::vec3 newPosition = cameraPosition + cameraFront * zoom;
            view = glm::lookAt(cameraPosition, newPosition, cameraUp);
        }

        if (proj == Projection::Orthographic) {
            projection = glm::ortho(-static_cast<float>(AppSettings::instance->ScreenWidth) /
                2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f *
                zoom, -static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f *
                zoom, static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f *
                zoom, -1000.0f, 1000.0f);


            view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        }
    }

    glm::mat4 GetProjectionMatrix() {
        return projection;
    }

    glm::mat4 GetView() {
        return view;
    }
};














//#pragma once
//#include "../../RequireLibs.h"
//#include "../../Graphics/StartEngineGraphics.h";
//#include "../../Graphics/AppSettings.h"
//
//using namespace std;
//
//class Camera {
//public:
//    glm::mat4 projection;
//    glm::mat4 view;
//    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
//    float zoom = 1;
//
//    void start() {
//        projection = glm::ortho(-static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, -static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, -1000.0f, 1000.0f);
//    }
//
//    void update() {
//        projection = glm::ortho(-static_cast<float>(AppSettings::instance->ScreenWidth) /
//            2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f *
//            zoom, -static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f *
//            zoom, static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f *
//            zoom, -1000.0f, 1000.0f);
//
//
//        view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
//    }
//
//    glm::mat4 GetProjectionMatrix() {
//        return projection;
//    }
//
//    glm::mat4 GetView() {
//        return view;
//    }
//};