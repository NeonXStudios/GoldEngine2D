#include "GoldEditor.h"

using namespace std;
GoldEditor* GoldEditor::editor = nullptr;
bool GoldEditor::testMode = true;
int width = 1920;
int height = 1080;
bool saved;

//Skybox* sky = new Skybox();


void GoldEditor::start() {
    ProjectPath = ProjectPath;
    uiMaster = new UIManager();

    uiMaster->start();
    std::cout << "Starting editor" << endl;
    SaveData::loadScene();
    //gizmos->create();
    //gizmos->start();
    //sky->init();
}


void GoldEditor::draw() {
}


void GoldEditor::update() {

    //if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
    //    glm::vec3 pos = UIManager::instance->inspectorui->ObjectSelectToInspector->transform->Position;
    //    glm::vec3 scale = UIManager::instance->inspectorui->ObjectSelectToInspector->transform->Scale;
    //     
    //    gizmos->DrawCapsule   (pos, 1, 1, glm::vec3(0, 1, 0));
    //}

#pragma region MOVE CAMERA
        GLFWwindow* window = StartEngineGraphics::window;


    if (activeMouse) {
        // Handles mouse inputs
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            /*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition += SceneManager::GetSceneManager()->OpenScene->worldCamera->speed * SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation;
            }

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition += SceneManager::GetSceneManager()->OpenScene->worldCamera->speed * -glm::normalize(glm::cross(SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation, SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraUp));
            }

            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition += SceneManager::GetSceneManager()->OpenScene->worldCamera->speed * -SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation;
            }

            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition += SceneManager::GetSceneManager()->OpenScene->worldCamera->speed * glm::normalize(glm::cross(SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation, SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraUp));
            }

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition += SceneManager::GetSceneManager()->OpenScene->worldCamera->speed * SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraUp;
            }

            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition += SceneManager::GetSceneManager()->OpenScene->worldCamera->speed * -SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraUp;
            }*/

            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->speed = 0.4f;
            }

            else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->speed = 0.1f;
            }


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
            //glm::vec3 newOrientation = glm::rotate(SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation, glm::radians(-rotX), glm::normalize(glm::cross(SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation, SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraUp)));
           /*
            if (abs(glm::angle(newOrientation, SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraUp) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation = newOrientation;
            }
            */
            //SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation = glm::rotate(SceneManager::GetSceneManager()->OpenScene->worldCamera->Orientation, glm::radians(-rotY), SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraUp);
            
            SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition.x += rotY;
            SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition.y -= rotX;
            UIManager::instance->rightClickui->locked = true;
            // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
            glfwSetCursorPos(window, (width / 2), (height / 2));
        }       
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        UIManager::instance->rightClickui->locked = false;
        // Unhides cursor since camera is not looking around anymore       
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // Makes sure the next time the camera looks around it doesn't jump
        firstClick = true;
    }
     
  /*  RayCastHit hit;


    if (InputSystem::InputSystem::GetKey(GLFW_KEY_LEFT_CONTROL) && InputSystem::InputSystem::GetKey(GLFW_KEY_S)) {
        if (!saved) {
            SaveData::saveScene();
            saved = true;
        }
    }
    else {
        saved = false;
    }

    Cast3D* cast = new Cast3D();

    if (cast->RayCast (SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition, 
                       SceneManager::GetSceneManager()->OpenScene->worldCamera->GetForwardInverse(), 
                       1000, 
                       &hit)) 
    {
        std::cout << "BOX FIND: " << hit.entity->ObjectName << std::endl;
    }*/

    uiMaster->update ();
#pragma endregion
}



void GoldEditor::PreRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    uiMaster->lateupdate();
}

void GoldEditor::PostRender() {
    //sky->update();

    uiMaster->fixupdate();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

    //string startPath = "C:\\Users\\tupap\\Documents\\GoldEngine\\Projects\\Vortex\\";
    string startPath = (string)argv[1];

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
