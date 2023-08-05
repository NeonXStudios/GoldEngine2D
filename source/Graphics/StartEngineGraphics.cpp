#include "StartEngineGraphics.h"
#include "../Graphics/AppSettings.h"
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/Sprite/SpriteComponent.h"
#include "../Components/UI/UIImplement.h"

GLFWwindow* StartEngineGraphics::window = nullptr;
EngineBehaviour* StartEngineGraphics::engine = nullptr;
StartEngineGraphics* StartEngineGraphics::instance = nullptr;
UIImplement* UIIMPL = new UIImplement();



void StartEngineGraphics::create() {
    if (StartEngineGraphics::instance) throw std::exception ("Graphics manager already exist");
    StartEngineGraphics::instance = new StartEngineGraphics();
    std::cout << "GRAPHIC MANAGER CREATED..." << endl;
}

void StartEngineGraphics::release() {
    if (!StartEngineGraphics::instance) return;
    delete StartEngineGraphics::instance;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    
    SceneManager::GetSceneManager()->OpenScene->worldCamera->projection = glm::ortho(-aspectRatio * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, aspectRatio * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, -SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, -1000.0f, 1000.0f);
}

void StartEngineGraphics::StartEngine () {
    glfwInit();
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    StartEngineGraphics::window = glfwCreateWindow(1920, 1080, "GOLD ENGINE", NULL, NULL);

    if (StartEngineGraphics::window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(StartEngineGraphics::window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwGetFramebufferSize (StartEngineGraphics::window, &AppSettings::instance->ScreenWidth, &AppSettings::instance->ScreenHeight);

    //START GAME
    SceneManager::GetSceneManager()->OpenScene->start();



    //LOAD IMGUI IMPLEMENTATION
    UIIMPL->start();




    //START GAME FUNCTION
    StartEngineGraphics::engine->start();
}

void StartEngineGraphics::update() {
    glfwPollEvents();
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    time += deltaTime;

    StartEngineGraphics::engine->lateupdate();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SceneManager::GetSceneManager()->OpenScene->update();
    StartEngineGraphics::engine->draw();
    StartEngineGraphics::engine->update();
    StartEngineGraphics::engine->fixupdate();

   
    UIIMPL->draw();                                                             

    //DRAW UI COMPONENTS
    UIIMPL->DrawCanvas();

    //DRAW ENGINE CANVAS UI
    StartEngineGraphics::engine->drawUI();

    //DRAW CANVAS DATA
    UIIMPL->DrawData();

    // Renderizar ImGUI
    glfwSwapBuffers(StartEngineGraphics::window);
}


void StartEngineGraphics::releasewindow() {
    StartEngineGraphics::engine->release();
    glfwTerminate();
}


void StartEngineGraphics::closeWindow() {
    glfwSetWindowShouldClose (StartEngineGraphics::window, GLFW_TRUE);
}