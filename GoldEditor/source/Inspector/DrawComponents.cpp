#include "DrawComponents.h"
#include "../UI/UIManager.h"

CAudio* audio = new CAudio();
CSprite* sprite = new CSprite();

void DrawComponents::start() {
	
}

void DrawComponents::update() {
	if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr && audio != nullptr) {
		Entity* obj = UIManager::instance->inspectorui->ObjectSelectToInspector;

		if (&obj->getComponent<AudioSource>() != nullptr) {
			audio->update (obj);
		}

		if (&obj->getComponent<SpriteComponent>() != nullptr) {
			sprite->update (obj);
		}
	}
}