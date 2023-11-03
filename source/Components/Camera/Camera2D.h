#pragma once
#include "../../RequireLibs.h"
#include "../../Graphics/StartEngineGraphics.h";
#include "../../Graphics/AppSettings.h"
#include "../ShaderCompiler/Shader.h"

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
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

    float fov = 25.0f;
    float zoom = 0.030f;

    // Quaterniones para las rotaciones
    glm::quat cameraRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    float rotationXAngle = 0.0f;
    float rotationYAngle = 0.0f;
    float rotationZAngle = 0.0f;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    bool firstClick = true;

    // Stores the width and height of the window
    int width = 1920;
    int height = 1080;

    // Adjust the speed of the camera and it's sensitivity when looking around
    float speed = 0.1f;
    float sensitivity = 100.0f;

    void start() {

    }

    void update() {
        // Aplicar las rotaciones en los ejes X, Y y Z a los quaterniones
        //Orientation.y = 0;

        float rotationXAngle360 = fmod(rotationXAngle, 360);
        float rotationYAngle360 = fmod(rotationYAngle, 360);
        float rotationZAngle360 = fmod(rotationZAngle, 360);

        // Aplicar las rotaciones en los ejes X, Y y Z a los quaterniones
        glm::quat rotationX = glm::angleAxis(glm::radians(rotationXAngle360), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::quat rotationY = glm::angleAxis(glm::radians(rotationYAngle360), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::quat rotationZ = glm::angleAxis(glm::radians(rotationZAngle360), glm::vec3(0.0f, 0.0f, 1.0f));


        // Combinar las rotaciones en un solo quaternion
        cameraRotation = rotationX * rotationY * rotationZ;


        // Convertir el quaternion a una matriz de rotaci�n
        glm::mat4 rotationMatrix = glm::mat4_cast(cameraRotation);


        if (proj == Projection::Perspective) {
            view = glm::lookAt(cameraPosition, cameraPosition + Orientation, cameraUp);
            projection = glm::perspective(glm::radians(fov), (float)AppSettings::RenderWidth / AppSettings::RenderHeight, 0.1f, 10000.0f);
            cameraMatrix = projection * view;
        }

        if (proj == Projection::Orthographic) {
            float screenWidth  = static_cast<float>   (AppSettings::RenderWidth );
            float screenHeight = static_cast<float>   (AppSettings::RenderHeight);
            projection = glm::ortho(-screenWidth / 2.0f * zoom, screenWidth / 2.0f * zoom, -screenHeight / 2.0f * zoom, screenHeight / 2.0f * zoom, -1000.0f, 1000.0f);

            Orientation = glm::mat3(rotationMatrix) * glm::vec3(0.0f, 0.0f, -1.0f);
            view = glm::lookAt(cameraPosition, cameraPosition + Orientation, cameraUp);
        }

        cameraUp    = glm::mat4 (rotationMatrix) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
        cameraFront = glm::mat4 (rotationMatrix) * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

        cameraPosition += cameraVelocity;
        cameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    glm::mat4 GetProjectionMatrix() {
        return projection;
    }

    glm::mat4 GetView() {
        return view;
    }
    
    glm::mat4 GetViewInverse() {
        return glm::inverse(view);
    }

    glm::vec3 GetRightInverse() {
        return -glm::normalize(glm::vec3(GetView()[0]));
    }

    glm::vec3 GetUpInverse() {
        return -glm::normalize(glm::vec3(GetView()[1]));
    }

    glm::vec3 GetForwardInverse() {
        return -glm::normalize(glm::vec3(GetView()[2]));
    }




    glm::vec3 GetForward () {
        return glm::normalize (glm::vec3 (GetViewInverse()[2]));
    }

    glm::vec3 GetRight() {
        return glm::normalize(glm::vec3  (GetViewInverse()[0]));
    }

    glm::vec3 GetUp() {
        return glm::normalize(glm::vec3  (GetViewInverse()[1]));
    }

    void Matrix(Shader& shader, const char* uniform)
    {
        // Exports camera matrix
       // glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(GetProjectionMatrix()));
    }

    glm::mat4 GetCameraMatrix() {
        return cameraMatrix;
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