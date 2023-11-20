#include "RigidBody.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include "nlohmann/json.hpp"
#include "../SaveSystem/CheckVar.h"


using namespace nlohmann;
using namespace std;

void RigidBody::init() {

	position = b2Vec2 (entity->transform->Position.x, entity->transform->Position.y);

	SpriteComponent* srp = &entity->getComponent <SpriteComponent>();
	float degrees = srp->rotationAngle;
	float radians = degrees * (b2_pi / 180.0f);
	dynamicBox = new b2PolygonShape();
	fixtureDef = new b2FixtureDef();

	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody;
	fixtureDef->shape = dynamicBox;
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	body = SceneManager::GetSceneManager()->OpenScene->GravityWorld->CreateBody(&bodyDef);

	b2Vec2 localCenter(0.0f, 0.0f);
	localCenter.Set(0, 0);
	dynamicBox->SetAsBox(float(srp->entity->transform->Scale.x * 0.5f), float(srp->entity->transform->Scale.y * 0.5f));
	fixtureDef->shape = dynamicBox;
	body->CreateFixture(fixtureDef);

	body->SetTransform(b2Vec2((float)position.x, (float)position.y), radians);

	UpdateCollisions();
	changeState (false);
}


void RigidBody::update() {
	if (!isStatic) {

		if (!FreezeX) {
			entity->transform->Position.x = body->GetPosition().x;
			body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
		}

		if (!FreezeY) {
			entity->transform->Position.y = -body->GetPosition().y;
			body->SetLinearVelocity (b2Vec2 (body->GetLinearVelocity().x, 0));
		}

		entity->transform->Rotation.x = -glm::degrees(body->GetAngle());
	}
	else {
		body->SetTransform(b2Vec2(float(entity->transform->Position.x), -float(entity->transform->Position.y)), -glm::radians(entity->transform->Rotation.x));
	}

	b2PolygonShape* boxShape = static_cast<b2PolygonShape*>(body->GetFixtureList()->GetShape());
	boxShape->SetAsBox(entity->transform->Scale.x, entity->transform->Scale.y);

	body->GetFixtureList()->SetSensor(isTrigger);
}


void RigidBody::draw() {

}


void RigidBody::UpdateCollisions() {
	SpriteComponent* srp = &entity->getComponent<SpriteComponent>();

	body->DestroyFixture(body->GetFixtureList());
	b2FixtureDef* fx = new b2FixtureDef();
	fx->density = density;
	fx->friction = friction;

	b2Vec2 localCenter(0.0f, 0.0f);
	localCenter.Set(0, 0);
	float boxWidth = srp->entity->transform->Scale.x;
	float boxHeight = srp->entity->transform->Scale.y;
	dynamicBox->SetAsBox(boxWidth, boxHeight, localCenter, 0);
	fx->shape = dynamicBox;
	fixtureDef = fx;

	body->CreateFixture(fx);
	body->GetFixtureList()->SetSensor(isTrigger);
}

void RigidBody::clean() {
	std::cout << "Componente rigidBody removido" << std::endl;
}

void RigidBody::changeState(bool val) {
	isStatic = val;
	float radians = -glm::radians (entity->transform->Rotation.x);

	if (!isStatic) {
		body->SetAwake(true);
		b2Vec2 newPosition(float(entity->transform->Position.x), float(-entity->transform->Position.y));
		body->SetTransform(newPosition, radians);
		body->SetType(b2_dynamicBody);
	}
	else {
		body->SetType(b2_staticBody);
		b2Vec2 newPosition(float(position.x), float(position.y));
		body->SetTransform(newPosition, radians);
	}

	body->SetAwake(true);
}


void RigidBody::triggerOn(Entity* enterEntity) {
	if (!usedTrigger) {

		if (entity->hasComponent<ScriptCompiler>()) {
			entity->getComponent<ScriptCompiler>().ontrigger (enterEntity);
		}

		std::cout << "MI OBJETO " << enterEntity->ObjectName << " ENTRO EN UNA COLISION" << std::endl;
		usedTrigger = true;
	}
}

void RigidBody::addForce(glm::vec2 force) {
	body->ApplyForce (b2Vec2 (force.x * 1000, force.y * 1000), body->GetPosition(), true);
	std::cout << "AGREGANDO FUERZA" << std::endl;
}


void RigidBody::triggerOff(Entity* enterEntity) {
	if (usedTrigger) {
		if (entity->hasComponent<ScriptCompiler>()) {
			entity->getComponent<ScriptCompiler>().ontriggerexit(enterEntity);
		}

		std::cout << "MI OBJETO " << enterEntity->ObjectName << " SALIO DE UNA COLISION" << std::endl;
		usedTrigger = false;
	}
}

std::string RigidBody::serialize() {
	json componentData;
	componentData["static"]		= isStatic;
	componentData["freezex"]	= FreezeX;
	componentData["freezey"]	= FreezeY;
	componentData["isTrigger"] = isTrigger;
	componentData["posx"] = body->GetPosition ().x;
	componentData["posy"]  = body->GetPosition().y;

	return componentData.dump();
}

void RigidBody::deserialize(std::string g, std::string) {
	json componentData = json::parse(g);

	if (CheckVar::Has (componentData, "static"))
	isStatic  = (bool)componentData["static"];
 
	if (CheckVar::Has(componentData, "freezex"))
	FreezeX   = (bool)componentData["freezex"];

	if (CheckVar::Has(componentData, "freezey"))
	FreezeY   = (bool)componentData["freezey"];

	if (CheckVar::Has(componentData, "isTrigger"))
	isTrigger = (bool)componentData["isTrigger"];

	float posX = 0;
	float posY = 0;

	if (CheckVar::Has(componentData, "posx"))
		posX = componentData["posx"];

	if (CheckVar::Has(componentData, "posy"))
		posY = componentData["posy"];


	SpriteComponent* srp = &entity->getComponent<SpriteComponent>();

	float degrees = srp->rotationAngle;
	float radians = degrees * (b2_pi / 180.0f);

	body->SetTransform (b2Vec2 (posX, posY), radians);

	if (!isStatic) {
		body->SetAwake(true);
		b2Vec2 newPosition(float(position.x), float(position.y));
		body->SetTransform(newPosition, radians);
		body->SetType(b2_dynamicBody);
	}
	else {
		body->SetType(b2_staticBody);
		b2Vec2 newPosition(float(position.x), float(position.y));
		body->SetTransform(newPosition, radians);
	}


	//body->SetTransform (b2Vec2(srp->ObjectPosition.x, -srp->ObjectPosition.y), srp->rotationAngle);
	//body->SetAwake(true);
}