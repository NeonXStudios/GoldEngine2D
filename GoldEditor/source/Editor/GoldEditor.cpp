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
#pragma region MOVE CAMERA
    //Camera* cam = SceneManager::GetSceneManager()->OpenScene->worldCamera;


    //glm::vec3 cameraDirection = glm::normalize(cam->cameraFront);
    //glm::vec3 cameraDirectio2 = glm::normalize(cam->cameraFront);

    //// Multiplicar el vector de dirección por la velocidad y sumarlo a la posición
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_W))
    //    cam->cameraPosition += cameraDirection * cameraSpeed;
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_S))
    //    cam->cameraPosition -= cameraDirection * cameraSpeed;
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_A))
    //    cam->cameraPosition += cameraDirectio2 * cameraSpeed;
    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_D))
    //    cam->cameraPosition += cameraDirectio2 * -cameraSpeed;

    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_UP)) {
    //    cam->rotationXAngle += 0.3f;
    //}

    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_DOWN)) {
    //    cam->rotationXAngle -= 0.3f;
    //}

    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_LEFT)) {
    //    cam->rotationYAngle += 0.3f;
    //}

    //if (InputSystem::InputSystem::GetKey(GLFW_KEY_RIGHT)) {
    //    cam->rotationYAngle -= 0.3f;
    //} 
    //   
#pragma endregion
    //sky->update();
}



void GoldEditor::PreRender() {
    uiMaster->lateupdate();
}

void GoldEditor::PostRender() {
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
