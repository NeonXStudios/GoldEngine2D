#include "StartEngineGraphics.h"
#include "../Graphics/AppSettings.h"
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/Sprite/SpriteComponent.h"
#include "../Components/UI/UIImplement.h"

GLFWwindow* StartEngineGraphics::window = nullptr;
EngineBehaviour* StartEngineGraphics::engine = nullptr;
StartEngineGraphics* StartEngineGraphics::instance = nullptr;
UIImplement* UIIMPL = new UIImplement();

unsigned int framebuffer;
unsigned int texture;

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


    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    UIIMPL->start();
}

void StartEngineGraphics::update() {
    glfwPollEvents();
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    time += deltaTime;


    /*
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    //CLEAN THE WINDOWS AND DRAW
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSetFramebufferSizeCallback(StartEngineGraphics::window, framebuffer_size_callback);

    // Update the projection matrix with zoom
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(StartEngineGraphics::window, &screenWidth, &screenHeight);


    //UPDATE SCENE AND DRAW
    SceneManager::GetSceneManager()->OpenScene->update();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
*/

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SceneManager::GetSceneManager()->OpenScene->update();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Copiar el contenido del framebuffer en la textura
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBindTexture(GL_TEXTURE_2D, texture);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
 
    UIIMPL->draw();
    //DRAW UI COMPONENTS
    UIIMPL->DrawCanvas();

    ImVec2 windowSize = ImVec2(1920, 1080);

    // Dibujamos la imagen en la ventana de ImGui
    ImGui::SetNextWindowSize(windowSize);
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    // Obtenemos el tamaño de la ventana de ImGui después de que se apliquen las restricciones de tamaño
    ImVec2 actualWindowSize = ImGui::GetWindowSize();
    float scaleFactor = std::min(actualWindowSize.x / windowSize.x, actualWindowSize.y / windowSize.y);
    ImVec2 imageSize = ImVec2(1920.0f * scaleFactor, 1080.0f * scaleFactor);

    // Calculamos la posición para centrar la imagen en la ventana
    ImVec2 imagePosition = ImVec2((actualWindowSize.x - imageSize.x) * 0.5f, (actualWindowSize.y - imageSize.y) * 0.5f);

    ImGui::SetCursorPos(imagePosition);

    // Invertimos las coordenadas de textura en el eje Y antes de mostrar la imagen
    ImGui::Image((void*)(intptr_t)texture, imageSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();



    //DRAW CANVAS DATA
    UIIMPL->DrawData();
    glfwSwapBuffers(StartEngineGraphics::window);
}


void StartEngineGraphics::releasewindow() {

    glfwTerminate();
}