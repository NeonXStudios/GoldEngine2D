#pragma once
#include <iostream>
#include "../../../source/EngineBehaviour/GoldEngineLib.h"
#include "../UI/UIManager.h"

class GoldEditor : public EngineBehaviour { 
public:
    static GoldEditor* editor;
    Entity* player;
    Entity* player2;
    Entity* player3;
    UIManager* uiMaster = new UIManager();

    void start() override {
        uiMaster->start();
        std::cout << "Starting editor" << endl;



        player = SceneManager::GetSceneManager()->NewEntity();
        player2 = SceneManager::GetSceneManager()->NewEntity();
        player3 = SceneManager::GetSceneManager()->NewEntity();

        player2->ObjectName = "OBJETO2";
        player3->ObjectName = "OBJETO3";
    }

    void draw() override {

    }

    void update() override {
        uiMaster->update();
        Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;
        float cameraSpeed = 1;

        if (InputSystem::InputSystem::GetKey(GLFW_KEY_W))
            cam->cameraPosition += glm::vec3(0.0f, 0.0f, cameraSpeed);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_S))
            cam->cameraPosition += glm::vec3(0.0f, 0.0f, -cameraSpeed);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_A))
            cam->cameraPosition += glm::vec3(-cameraSpeed, 0.0f, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_D))
            cam->cameraPosition += glm::vec3(cameraSpeed, 0.0f, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_E))
            cam->cameraPosition += glm::vec3(0.0f, cameraSpeed, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_Q))
            cam->cameraPosition += glm::vec3(0.0f, -cameraSpeed, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_UP))
            cam->zoom -= 0.01f / 2;
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_DOWN))
            cam->zoom += 0.01f / 2;

        if (InputSystem::InputSystem::GetKey(GLFW_KEY_T)) {
            cam->cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
            cam->zoom = 1;
        }
    }

    void lateupdate() override {
        uiMaster->lateupdate();
    }

    void fixupdate() override {
        uiMaster->fixupdate();
    }

    void drawUI() override {
        uiMaster->draw();
    }

    void release() override {
       
    }
};