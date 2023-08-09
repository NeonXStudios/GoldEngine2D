#include "CAudio.h"
#include "../../UI/EditorUI/EditorGUI.h"


void CAudio::start() {

}


void CAudio::update (Entity* owner) {
	EditorGUI::Text ("Audio Source");
	string g = EditorGUI::InputText ("Audio Path", "HOLA");
}