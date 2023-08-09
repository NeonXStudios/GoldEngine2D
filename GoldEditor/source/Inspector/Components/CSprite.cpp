#include "CSprite.h"


void CSprite::start() {

}

void CSprite::update (Entity* owner) {
	EditorGUI::Text("Sprite");
	owner->getComponent<SpriteComponent>().TexturePath = EditorGUI::InputText ("File Path", owner->getComponent<SpriteComponent>().TexturePath);
}