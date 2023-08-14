#include "GoldEditor.h"


GoldEditor* GoldEditor::editor = nullptr;



int main()
{
    if (GoldEditor::editor) throw std::exception("GoldEditor already created.");
    GoldEditor::editor = new GoldEditor();
    std::cout << "GoldEditor Created" << endl;

    RunEngine* engine = new RunEngine();
    AppSettings::setTargetFrame (1);


    //GLD::SaveSystem* g = new GLD::SaveSystem();

    //if (g->save("game/assets/saves", "scene.f", )) {
    //    std::cout << "ARCHIVO ESCRITO CON EXITO!" << endl;
    //}
    //else {
    //    std::cout << "NO SE LOGRO ESCRIBIR EL ARCHIVO!" << endl;
    //}

    //std::cout << "--------" << g->load("game/assets/saves", "scene.f") << std::endl;

    engine->StartGameEngine(GoldEditor::editor);
    std::cout << "Game finish" << endl;
    return 0;
}