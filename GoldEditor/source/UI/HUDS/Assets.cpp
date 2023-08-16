#include "Assets.h"
#include "../../Editor/GoldEditor.h"

void AssetsUI::resetRoute() {
	path_to_read = GoldEditor::editor->ProjectPath + "/assets/";
}


string AssetsUI::getRoute() {
	return GoldEditor::editor->ProjectPath;
}