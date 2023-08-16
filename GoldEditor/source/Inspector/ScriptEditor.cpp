#include "ScriptEditor.h"
#include "../Editor/GoldEditor.h"

void ScriptEditor::setupPath() {
	gPath = GoldEditor::editor->ProjectPath;
}