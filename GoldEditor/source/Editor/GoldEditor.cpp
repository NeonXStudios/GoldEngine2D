#include "GoldEditor.h"


GoldEditor* GoldEditor::editor = nullptr;

using namespace std;


int main (int argc, char* argv[])
{
    if (argv[1] == nullptr) {
        std::cout << "Project path not found" << std::endl;
        return 54;
    }

    if (GoldEditor::editor) throw std::exception("GoldEditor already created.");
    GoldEditor::editor = new GoldEditor();
    GoldEditor::editor->ProjectPath = (string)argv[1];
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