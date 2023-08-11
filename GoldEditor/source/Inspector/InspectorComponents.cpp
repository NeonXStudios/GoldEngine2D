#include "InspectorComponents.h"
#include "ComponentUIDrawer.h"



void InspectorComponents::update(Entity* ownerActor) {
	//OLD COMPONENT FIND

	//CAudio au = CAudio();
	//CSprite ae = CSprite();
	//CScript csrp = CScript();
	//CRigidBody rgBody = CRigidBody();

	//ae.update			<SpriteComponent>	     (ownerActor, 3);
	//au.update			<AudioSource>            (ownerActor, 0);
	//csrp.update			<ScriptCompiler>		 (ownerActor, 1);
	//rgBody.update		<RigidBody>			     (ownerActor, 2);


	ComponentUIDrawer::updateUI		<SpriteComponent>			(ownerActor, 0, new CSprite());
	ComponentUIDrawer::updateUI		<ScriptCompiler>			(ownerActor, 1, new CScript());
	ComponentUIDrawer::updateUI		<AudioSource>				(ownerActor, 2, new CAudio());
	ComponentUIDrawer::updateUI		<RigidBody>					(ownerActor, 3, new CRigidBody());

}