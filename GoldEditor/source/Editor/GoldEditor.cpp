#include "GoldEditor.h"


GoldEditor* GoldEditor::editor = nullptr;

int main()
{
    GoldEditor::editor = new GoldEditor();

    RunEngine* engine = new RunEngine();
    AppSettings::setTargetFrame (165);
    engine->StartGameEngine(GoldEditor::editor);
    std::cout << "Game finish" << endl;
    return 0;
}