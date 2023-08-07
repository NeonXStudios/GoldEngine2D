#include "GoldEditor.h"


GoldEditor* GoldEditor::editor = nullptr;

int main()
{
    if (GoldEditor::editor) throw std::exception("GoldEditor already created.");
    GoldEditor::editor = new GoldEditor();
    std::cout << "GoldEditor Created" << endl;

    RunEngine* engine = new RunEngine();
    AppSettings::setTargetFrame (165);
    engine->StartGameEngine(GoldEditor::editor);
    std::cout << "Game finish" << endl;
    return 0;
}