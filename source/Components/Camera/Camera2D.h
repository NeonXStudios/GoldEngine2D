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

    Projection proj = Projection::Perspective;
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);  // Direcci�n hacia la que mira la c�mara
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);     // Vector hacia arriba de la c�mara
    float fov = 45.0f;  // Campo de visi�n en grados
    float zoom = 1.0f;

    // Quaterniones para las rotaciones
    glm::quat cameraRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    float rotationXAngle = 0.0f;
    float rotationYAngle = 0.0f;
    float rotationZAngle = 0.0f;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    bool firstClick = true;

    // Stores the width and height of the window
    int width = 1920;
    int height = 1080;

    // Adjust the speed of the camera and it's sensitivity when looking around
    float speed = 0.1f;
    float sensitivity = 100.0f;

    void start() {
        //projection = glm::ortho(-static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, -static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, -1000.0f, 1000.0f);
    }

    void update() {
        // Aplicar las rotaciones en los ejes X, Y y Z a los quaterniones
        float rotationXAngle360 = fmod(rotationXAngle, 360);
        float rotationYAngle360 = fmod(rotationYAngle, 360);
        float rotationZAngle360 = fmod(rotationZAngle, 360);

        // Aplicar las rotaciones en los ejes X, Y y Z a los quaterniones
        glm::quat rotationX = glm::angleAxis(glm::radians(rotationXAngle360), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::quat rotationY = glm::angleAxis(glm::radians(rotationYAngle360), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::quat rotationZ = glm::angleAxis(glm::radians(rotationZAngle360), glm::vec3(0.0f, 0.0f, 1.0f));

        // Combinar las rotaciones en un solo quaternion
        cameraRotation = rotationZ * rotationY * rotationX;

        // Convertir el quaternion a una matriz de rotaci�n
        glm::mat4 rotationMatrix = glm::mat4_cast(cameraRotation);

        if (proj == Projection::Perspective) {
            //float aspectRatio = static_cast<float>(AppSettings::instance->ScreenWidth) / static_cast<float>(AppSettings::instance->ScreenHeight);
            //projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 10000000.0f);

            //// Aplicar la rotaci�n a la direcci�n de la c�mara usando la matriz de rotaci�n
            //cameraFront = glm::mat3(rotationMatrix) * glm::vec3(0.0f, 0.0f, -1.0f);

            //// Calcular la nueva posici�n de la c�mara
            //glm::vec3 newPosition = cameraPosition + cameraFront * zoom;
            //view = glm::lookAt(cameraPosition, newPosition, cameraUp);

            // Makes camera look in the right direction from the right position
            view = glm::lookAt(cameraPosition, cameraPosition + Orientation, cameraUp);
            // Adds perspective to the scene
            projection = glm::perspective(glm::radians(fov), (float)1920 / 1080, 0.1f, 10000.0f);

            // Sets new camera matrix
            cameraMatrix = projection * view;
        }

        if (proj == Projection::Orthographic) {
            float screenWidth = static_cast<float>(AppSettings::instance->ScreenWidth);
            float screenHeight = static_cast<float>(AppSettings::instance->ScreenHeight);
            projection = glm::ortho(-screenWidth / 2.0f * zoom, screenWidth / 2.0f * zoom,
                -screenHeight / 2.0f * zoom, screenHeight / 2.0f * zoom, -1000.0f, 1000.0f);

            // Aplicar la rotaci�n a la direcci�n de la c�mara usando la matriz de rotaci�n
            cameraFront = glm::mat3(rotationMatrix) * glm::vec3(0.0f, 0.0f, -1.0f);

            view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
        }


        GLFWwindow* window = StartEngineGraphics::window;




        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            cameraPosition += speed * Orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            cameraPosition += speed * -glm::normalize(glm::cross(Orientation, cameraUp));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            cameraPosition += speed * -Orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            cameraPosition += speed * glm::normalize(glm::cross(Orientation, cameraUp));
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            cameraPosition += speed * cameraUp;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            cameraPosition += speed * -cameraUp;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            speed = 0.4f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            speed = 0.1f;
        }


        // Handles mouse inputs
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            // Hides mouse cursor
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            // Prevents camera from jumping on the first click
            if (firstClick)
            {
                glfwSetCursorPos(window, (width / 2), (height / 2));
                firstClick = false;
            }

            // Stores the coordinates of the cursor
            double mouseX;
            double mouseY;
            // Fetches the coordinates of the cursor
            glfwGetCursorPos(window, &mouseX, &mouseY);

            // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
            // and then "transforms" them into degrees 
            float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
            float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

            // Calculates upcoming vertical change in the Orientation
            glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, cameraUp)));

            // Decides whether or not the next vertical Orientation is legal or not
            if (abs(glm::angle(newOrientation, cameraUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                Orientation = newOrientation;
            }

            // Rotates the Orientation left and right
            Orientation = glm::rotate(Orientation, glm::radians(-rotY), cameraUp);

            // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
            glfwSetCursorPos(window, (width / 2), (height / 2));
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            // Unhides cursor since camera is not looking around anymore
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            // Makes sure the next time the camera looks around it doesn't jump
            firstClick = true;
        }
    }

    glm::mat4 GetProjectionMatrix() {
        return projection;
    }

    glm::mat4 GetView() {
        return view;
    }

    void Matrix(Shader& shader, const char* uniform)
    {
        // Exports camera matrix
       // glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(GetProjectionMatrix()));
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