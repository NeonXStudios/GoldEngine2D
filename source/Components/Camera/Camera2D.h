#ifndef CAMERA2D_H
#define CAMERA2D_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Graphics/StartEngineGraphics.h";
#include "../../Graphics/AppSettings.h"

using namespace std;

class Camera {
public:
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 10.0f);
    float zoom = 1;

    void processInput(GLFWwindow* window) {
        float cameraSpeed = 1;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPosition += glm::vec3(0.0f, 0.0f, cameraSpeed); 
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPosition += glm::vec3(0.0f, 0.0f, -cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPosition += glm::vec3(-cameraSpeed, 0.0f, 0.0f);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPosition += glm::vec3(cameraSpeed, 0.0f, 0.0f);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            cameraPosition += glm::vec3(0.0f, cameraSpeed, 0.0f);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            cameraPosition += glm::vec3(0.0f, -cameraSpeed, 0.0f);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            zoom -= 0.01f / 2;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            zoom += 0.01f / 2;
        
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
            zoom = 1;
        }
    }

    void start() {
        projection = glm::ortho(-static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenWidth) / 2.0f * zoom, -static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, static_cast<float>(AppSettings::instance->ScreenHeight) / 2.0f * zoom, -1000.0f, 1000.0f);
    }

    void update() {
        processInput (StartEngineGraphics::window);
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