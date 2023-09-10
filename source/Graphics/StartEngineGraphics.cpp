#include "StartEngineGraphics.h"
#include "../Graphics/AppSettings.h"
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/Sprite/SpriteComponent.h"
#include "../Components/UI/UIImplement.h"
#include "../EngineBehaviour/GoldEngineLib.h"
#include <math.h>

GLFWwindow* StartEngineGraphics::window = nullptr;
EngineBehaviour* StartEngineGraphics::engine = nullptr;
StartEngineGraphics* StartEngineGraphics::instance = nullptr;
UIImplement* UIIMPL = new UIImplement();
Skybox* sky = new Skybox();


void StartEngineGraphics::create() {
    if (StartEngineGraphics::instance) throw std::exception ("Graphics manager already exist");
    StartEngineGraphics::instance = new StartEngineGraphics();
    std::cout << "GRAPHIC MANAGER CREATED..." << endl;
}

void StartEngineGraphics::release() {
    if (!StartEngineGraphics::instance) return;
    delete StartEngineGraphics::instance;
}

void StartEngineGraphics::StartEngine () {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    //LOAD IMGUI IMPLEMENTATION
    gameStarted = true;



    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    sky->init();
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
        glDepthFunc(GL_LESS);


        
        glDepthMask  (GL_FALSE);
        sky->update();
        glDepthMask  (GL_TRUE);

        glDepthFunc(GL_ALWAYS);

        SceneManager::GetSceneManager()->OpenScene->draw();
        StartEngineGraphics::engine->draw();



        SceneManager::GetSceneManager()->OpenScene->update();
        StartEngineGraphics::engine->update();
 




        SceneManager::GetSceneManager()->OpenScene->PostRender();
        StartEngineGraphics::engine->PostRender();

        AudioManager::GetManager()->Update();


        RenderImgui();


        // INTERCAMBIO DE BUFERES Y PRESENTACION
        glfwSwapBuffers(StartEngineGraphics::window);
    }
}



void StartEngineGraphics::RenderOpenGL() {

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