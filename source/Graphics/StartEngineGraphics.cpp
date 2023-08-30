#include "StartEngineGraphics.h"
#include "../Graphics/AppSettings.h"
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/Sprite/SpriteComponent.h"
#include "../Components/UI/UIImplement.h"
#include "../EngineBehaviour/GoldEngineLib.h"

GLFWwindow* StartEngineGraphics::window = nullptr;
EngineBehaviour* StartEngineGraphics::engine = nullptr;
StartEngineGraphics* StartEngineGraphics::instance = nullptr;
UIImplement* UIIMPL = new UIImplement();


GLuint imguiFramebuffer;
GLuint imguiTexture;


void StartEngineGraphics::create() {
    if (StartEngineGraphics::instance) throw std::exception ("Graphics manager already exist");
    StartEngineGraphics::instance = new StartEngineGraphics();
    std::cout << "GRAPHIC MANAGER CREATED..." << endl;
}

void StartEngineGraphics::release() {
    if (!StartEngineGraphics::instance) return;
    delete StartEngineGraphics::instance;
}

//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//    glViewport(0, 0, width, height);
//    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
//    
//    SceneManager::GetSceneManager()->OpenScene->worldCamera->projection = glm::ortho(-aspectRatio * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, aspectRatio * SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, -SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, SceneManager::GetSceneManager()->OpenScene->worldCamera->zoom, -1000.0f, 1000.0f);
//}

void StartEngineGraphics::StartEngine () {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Cambia este número a la versión exacta que desees (4.1, 4.2, etc.)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



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




    //START GAME FUNCTION
    StartEngineGraphics::engine->start();

    UIIMPL->start();
    //glGenFramebuffers(1, &imguiFramebuffer);
    //glBindFramebuffer(GL_FRAMEBUFFER, imguiFramebuffer);

    //glGenTextures(1, &imguiTexture);
    //glBindTexture(GL_TEXTURE_2D, imguiTexture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, AppSettings::ScreenWidth, AppSettings::ScreenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, imguiTexture, 0);


    //LOAD IMGUI IMPLEMENTATION
    gameStarted = true;



    // Crear y adjuntar el buffer de profundidad para la escena 3D
    glEnable(GL_DEPTH_TEST);
    // Enables Cull Facing
    glEnable(GL_CULL_FACE);
    // Keeps front faces
    glCullFace(GL_FRONT);
    // Uses counter clock-wise standard
    glFrontFace(GL_CCW);
}

void StartEngineGraphics::update() {
    if (gameStarted) {
        int width, height;

        glfwPollEvents();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        time += deltaTime;

        // RENDERIZACION DE TODO OPENGL
        StartEngineGraphics::engine->PreRender();
        SceneManager::GetSceneManager()->OpenScene->PreRender();

        // LIMPIEZA DEL BUFFER DE PROFUNDIDAD PARA LA ESCENA 3D
        //glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glfwGetFramebufferSize(StartEngineGraphics::window, &width, &height);
        AppSettings::RenderHeight = height;
        AppSettings::RenderWidth = width;

        glViewport(0, 0, AppSettings::RenderWidth, AppSettings::RenderHeight);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //RenderOpenGL();
        //glDepthFunc(GL_LESS);d
        //glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        SceneManager::GetSceneManager()->OpenScene->draw();
        StartEngineGraphics::engine->draw();

        SceneManager::GetSceneManager()->OpenScene->update();
        StartEngineGraphics::engine->update();


        SceneManager::GetSceneManager()->OpenScene->PostRender();
        StartEngineGraphics::engine->PostRender();

        RenderImgui();


        //glBindFramebuffer(GL_FRAMEBUFFER, imguiFramebuffer);
        //glBindFramebuffer(GL_READ_FRAMEBUFFER, imguiFramebuffer);
        //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        //glBlitFramebuffer(0, 0, AppSettings::RenderWidth, AppSettings::RenderHeight, 0, 0, AppSettings::RenderWidth, AppSettings::RenderHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);




        bool isDepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
        if (isDepthTestEnabled) {
            std::cout << "DEPTH IS ENABLED" << std::endl;
        }
        else {
            std::cout << "DEPTH IS DISABLED" << std::endl;
        }


        // INTERCAMBIO DE BUFERES Y PRESENTACION
        glfwSwapBuffers(StartEngineGraphics::window);
    }
}



void StartEngineGraphics::RenderOpenGL() {
    //glViewport(0, 0, AppSettings::ScreenWidth, AppSettings::ScreenHeight);
    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void StartEngineGraphics::RenderImgui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    StartEngineGraphics::engine->drawUI();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void StartEngineGraphics::releasewindow() {
    StartEngineGraphics::engine->release();
    glfwTerminate();
}


void StartEngineGraphics::closeWindow() {
    glfwSetWindowShouldClose (StartEngineGraphics::window, GLFW_TRUE);
}