#include "InspectorComponents.h"



void InspectorComponents::update(Entity* ownerActor) {
	CAudio au = CAudio();
	CSprite ae = CSprite();

	au.update <AudioSource>(ownerActor);
	ae.update <SpriteComponent>(ownerActor);
}