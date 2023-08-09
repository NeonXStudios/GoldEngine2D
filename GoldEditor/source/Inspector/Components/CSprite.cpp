#include "CSprite.h"


void CSprite::start() {

}

void CSprite::draw (Entity* owner) {
	EditorGUI::Text("Sprite");
	string newPath = EditorGUI::InputText("File Path", owner->getComponent<SpriteComponent>().TexturePath);
	if (owner->getComponent<SpriteComponent>().TexturePath != newPath) {
		owner->getComponent<SpriteComponent>().TexturePath = newPath;
		owner->getComponent<SpriteComponent>().LoadTexture();
	}
}