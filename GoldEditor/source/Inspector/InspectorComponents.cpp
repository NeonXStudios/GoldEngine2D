#include "InspectorComponents.h"



void InspectorComponents::update(Entity* ownerActor) {
	CAudio au = CAudio();
	CSprite ae = CSprite();
	CScript csrp = CScript();

	au.update		<AudioSource>            (ownerActor);
	ae.update		<SpriteComponent>	     (ownerActor);
	csrp.update		<ScriptCompiler>		 (ownerActor);
}