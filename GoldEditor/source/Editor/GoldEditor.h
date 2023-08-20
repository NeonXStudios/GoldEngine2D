#pragma once
#include <iostream>

#include "../../../source/EngineBehaviour/GoldEngineLib.h"
#include "../UI/UIManager.h"
#include "../Components/Data/SaveData.h"
#include <imguizmo/ImGuizmo.h>
#include "../Gizmos/MoveGizmos.h"


class GoldEditor : public EngineBehaviour { 
public:
    static GoldEditor* editor;
    UIManager* uiMaster;
    MoveGizmos* gizmos;
    string ProjectPath = "";
    Entity* ent;
    float cameraSpeed = 1;

    void start() override {
        ProjectPath = ProjectPath;
        uiMaster = new UIManager();
        gizmos = new MoveGizmos();

        uiMaster->start();
        std::cout << "Starting editor" << endl;
        SaveData::loadScene();
        gizmos->start();

        ent = SceneManager::GetSceneManager()->NewEntity();
        ent->addComponent <Skybox>();
    }

    void draw() override {
        gizmos->draw();
    }

    void update() override {

        uiMaster->update();
        Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;


        glm::vec3 cameraDirection = glm::normalize(cam->cameraFront);

        // Multiplicar el vector de dirección por la velocidad y sumarlo a la posición
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_W))
            cam->cameraPosition += cameraDirection * cameraSpeed;
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_S))
            cam->cameraPosition -= cameraDirection * cameraSpeed;
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_A))
            cam->cameraPosition += glm::vec3(cameraSpeed, 0.0f, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_D))
            cam->cameraPosition += glm::vec3(-cameraSpeed, 0.0f, 0.0f);

        /*
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_W))
            cam->cameraPosition += glm::vec3(0.0f, 0.0f, cameraSpeed);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_S))
            cam->cameraPosition += glm::vec3(0.0f, 0.0f, -cameraSpeed);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_A))
            cam->cameraPosition += glm::vec3(cameraSpeed, 0.0f, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_D))
            cam->cameraPosition += glm::vec3(-cameraSpeed, 0.0f, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_E))
            cam->cameraPosition += glm::vec3(0.0f, -cameraSpeed, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_Q))
            cam->cameraPosition += glm::vec3(0.0f, cameraSpeed, 0.0f);
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_UP))
            cam->zoom -= 0.01f / 2;
        if (InputSystem::InputSystem::GetKey(GLFW_KEY_DOWN))
            cam->zoom += 0.01f / 2;

        if (InputSystem::InputSystem::GetKey(GLFW_KEY_T)) {
            cam->cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
            cam->zoom = 1;
        }
        */

        if (InputSystem::InputSystem::GetKey(GLFW_KEY_UP)) {
            cam->rotationXAngle += 0.3f;
        }

        if (InputSystem::InputSystem::GetKey(GLFW_KEY_DOWN)) {
            cam->rotationXAngle -= 0.3f;
        }

        if (InputSystem::InputSystem::GetKey(GLFW_KEY_LEFT)) {
            cam->rotationYAngle += 0.3f;
        }

        if (InputSystem::InputSystem::GetKey(GLFW_KEY_RIGHT)) {
            cam->rotationYAngle -= 0.3f;
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