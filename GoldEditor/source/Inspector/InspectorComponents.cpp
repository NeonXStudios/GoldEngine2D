#include "InspectorComponents.h"



void InspectorComponents::update(Entity* ownerActor) {
	CAudio au = CAudio();
	CSprite ae = CSprite();
	CScript csrp = CScript();
	CRigidBody rgBody = CRigidBody();

	au.update		<AudioSource>            (ownerActor);
	ae.update		<SpriteComponent>	     (ownerActor);
	csrp.update		<ScriptCompiler>		 (ownerActor);
	rgBody.update		<RigidBody>		     (ownerActor);
}