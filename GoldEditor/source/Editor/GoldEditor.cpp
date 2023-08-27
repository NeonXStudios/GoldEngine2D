#include "GoldEditor.h"
#include "../Gizmos/GDGizmos.h"

using namespace std;
GoldEditor* GoldEditor::editor = nullptr;
bool GoldEditor::testMode = true;
//Skybox* sky = new Skybox();

void GoldEditor::start() {
    ProjectPath = ProjectPath;
    uiMaster = new UIManager();

    uiMaster->start();
    std::cout << "Starting editor" << endl;
    SaveData::loadScene();
    //sky->init();
}



void GoldEditor::draw() {

}


void GoldEditor::update() {
    //sky->update();
    uiMaster->update();
    Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;


    glm::vec3 cameraDirection = glm::normalize(cam->cameraFront);
    glm::vec3 cameraDirectio2 = glm::normalize(cam->cameraFront);

    // Multiplicar el vector de dirección por la velocidad y sumarlo a la posición
    if (InputSystem::InputSystem::GetKey(GLFW_KEY_W))
        cam->cameraPosition += cameraDirection * cameraSpeed;
    if (InputSystem::InputSystem::GetKey(GLFW_KEY_S))
        cam->cameraPosition -= cameraDirection * cameraSpeed;
    if (InputSystem::InputSystem::GetKey(GLFW_KEY_A))
        cam->cameraPosition += cameraDirectio2 * cameraSpeed;
    if (InputSystem::InputSystem::GetKey(GLFW_KEY_D))
        cam->cameraPosition += cameraDirectio2 * -cameraSpeed;

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


    //Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;
    //vec3 Orientation = glm::vec3 (cam->rotationXAngle, cam->rotationYAngle, cam->rotationZAngle);


    //if (InputSystem::InputSystem::GetKey (GLFW_KEY_W))
    //{
    //    cam->cameraPosition += cameraSpeed * Orientation;
    //}
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_A))
    //{
    //    cam->cameraPosition += cameraSpeed * -glm::normalize(glm::cross(Orientation, cam->cameraUp));
    //}
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_S))
    //{
    //    cam->cameraPosition += cameraSpeed * -Orientation;
    //}
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_D))
    //{
    //    cam->cameraPosition += cameraSpeed * glm::normalize(glm::cross(Orientation, cam->cameraUp));
    //}
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_SPACE))
    //{
    //    cam->cameraPosition += cameraSpeed * cam->cameraUp;
    //}
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_LEFT_CONTROL))
    //{
    //    cam->cameraPosition += cameraSpeed * -cam->cameraUp;
    //}
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_LEFT_SHIFT))
    //{
    //    cameraSpeed = 0.4f;
    //}
    //else {
    //    cameraSpeed = 0.1f;
    //}

    //float width = AppSettings::ScreenWidth;
    //float height = AppSettings::ScreenHeight;

    //GLFWwindow* window = StartEngineGraphics::window;


    //if (activeMouse) {
    //    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    //    {
    //        // Hides mouse cursor
    //        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    //        // Prevents camera from jumping on the first click
    //        if (firstClick)
    //        {
    //            glfwSetCursorPos(window, (width / 2), (height / 2));
    //            firstClick = false;
    //        }

    //        // Stores the coordinates of the cursor
    //        double mouseX;
    //        double mouseY;
    //        // Fetches the coordinates of the cursor
    //        glfwGetCursorPos(window, &mouseX, &mouseY);

    //        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
    //        // and then "transforms" them into degrees 
    //        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
    //        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

    //        // Calculates upcoming vertical change in the Orientation
    //        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, cam->cameraUp)));

    //        // Decides whether or not the next vertical Orientation is legal or not
    //        if (abs(glm::angle(newOrientation, cam->cameraUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
    //        {
    //            Orientation = newOrientation;
    //        }

    //        // Rotates the Orientation left and right
    //        Orientation = glm::rotate(Orientation, glm::radians(-rotY), cam->cameraUp);

    //        // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
    //        glfwSetCursorPos(window, (width / 2), (height / 2));
    //    }
    //    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    //    {
    //        // Unhides cursor since camera is not looking around anymore
    //        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    //        // Makes sure the next time the camera looks around it doesn't jump
    //        firstClick = true;
    //    }
    //}
}



void GoldEditor::lateupdate() {
    uiMaster->lateupdate();
}

void GoldEditor::fixupdate() {
    uiMaster->fixupdate();
}

void GoldEditor::drawUI() {
    uiMaster->draw();
}

void GoldEditor::release() {

}




int main (int argc, char* argv[])
{
    if (argv[1] == nullptr && !GoldEditor::testMode) {
        std::cout << "Project path not found" << std::endl;
        return 54;
    }

    string startPath = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\";

    if (GoldEditor::editor) throw std::exception("GoldEditor already created.");
    GoldEditor::editor = new GoldEditor();
    GoldEditor::editor->ProjectPath = startPath/*(string)argv[1]*/;
    GoldEditor::editor->GamePath = startPath;
    RunEngine* engine = new RunEngine();
   // AppSettings::setTargetFrame (1);


    //GLD::SaveSystem* g = new GLD::SaveSystem();

    //if (g->save("game/assets/saves", "scene.f", )) {
    //    std::cout << "ARCHIVO ESCRITO CON EXITO!" << endl;
    //}
    //else {
    //    std::cout << "NO SE LOGRO ESCRIBIR EL ARCHIVO!" << endl;
    //}

    //std::cout << "--------" << g->load("game/assets/saves", "scene.f") << std::endl;

    engine->StartGameEngine(GoldEditor::editor, false);
    std::cout << "Game finish" << endl;
    return 0;
}
