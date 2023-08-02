#include "StartEngineGraphics.h"
#include "../Graphics/AppSettings.h"
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/Sprite/SpriteComponent.h"
#include "../Components/UI/UIImplement.h"

GLFWwindow* StartEngineGraphics::window = nullptr;
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
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    StartEngineGraphics::window = glfwCreateWindow(800, 600, "GOLD ENGINE", NULL, NULL);

    if (StartEngineGraphics::window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(StartEngineGraphics::window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwGetFramebufferSize (StartEngineGraphics::window, &AppSettings::instance->ScreenWidth, &AppSettings::instance->ScreenHeight);
    SceneManager::GetSceneManager()->OpenScene->start();
    UIIMPL->start();
}

void StartEngineGraphics::update() {
    glfwPollEvents();
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    time += deltaTime;

    //CLEAN THE WINDOWS AND DRAW
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSetFramebufferSizeCallback(StartEngineGraphics::window, framebuffer_size_callback);

    // Update the projection matrix with zoom
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(StartEngineGraphics::window, &screenWidth, &screenHeight);


    //UPDATE SCENE AND DRAW
    SceneManager::GetSceneManager()->OpenScene->update();


 
    UIIMPL->draw();
    //DRAW UI COMPONENTS
    UIIMPL->DrawCanvas();
    //DRAW CANVAS DATA
    UIIMPL->DrawData();
    glfwSwapBuffers(StartEngineGraphics::window);
}

void StartEngineGraphics::releasewindow() {

    glfwTerminate();
}