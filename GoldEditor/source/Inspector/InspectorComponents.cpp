#include "InspectorComponents.h"



void InspectorComponents::update(Entity* ownerActor) {
	CAudio au = CAudio();
	CSprite ae = CSprite();
	CScript csrp = CScript();
	CRigidBody rgBody = CRigidBody();

	ae.update			<SpriteComponent>	     (ownerActor, 3);
	au.update			<AudioSource>            (ownerActor, 0);
	csrp.update			<ScriptCompiler>		 (ownerActor, 1);
	rgBody.update		<RigidBody>			     (ownerActor, 2);
}