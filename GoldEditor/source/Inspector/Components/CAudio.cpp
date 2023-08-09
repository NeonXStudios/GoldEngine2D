#include "CAudio.h"
#include "../../UI/EditorUI/EditorGUI.h"


void CAudio::start() {

}


void CAudio::draw (Entity* owner) {
	EditorGUI::Text ("Audio Source");
	string pathSound = EditorGUI::InputText("Audio Path", owner->getComponent<AudioSource>().AudioPath);

	if (owner->getComponent<AudioSource>().AudioPath != pathSound) {
		owner->getComponent<AudioSource>().AudioPath = pathSound;
	}
	std::cout << "AUDIO SOURCE INSPECTOR RUNNING" << std::endl;
}