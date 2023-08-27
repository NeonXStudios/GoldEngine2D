#include "InspectorComponents.h"
#include "ComponentUIDrawer.h"



void InspectorComponents::update(Entity* ownerActor) {
	ComponentUIDrawer::updateUI		<SpriteComponent>			(ownerActor, 0, new CSprite				()			);
	ComponentUIDrawer::updateUI		<ScriptCompiler>			(ownerActor, 1, new CScript				()			);
	ComponentUIDrawer::updateUI		<AudioSource>				(ownerActor, 2, new CAudio				()			);
	ComponentUIDrawer::updateUI		<RigidBody>					(ownerActor, 3, new CRigidBody			()			);
	ComponentUIDrawer::updateUI		<Rigidbody3d>			    (ownerActor, 4, new CRigidbody3D		()			);
	ComponentUIDrawer::updateUI		<BoxCollider>			    (ownerActor, 5, new CBoxCollider3D		()			);
}