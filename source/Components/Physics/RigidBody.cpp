#include "RigidBody.h"



void RigidBody::init() {
	SpriteComponent* srp = &entity->getComponent <SpriteComponent>();

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
	dynamicBox->SetAsBox(float(srp->Scale.x * srp->GlobalScale * 0.5f), float(srp->Scale.y * srp->GlobalScale * 0.5f));
	fixtureDef->shape = dynamicBox;
	body->CreateFixture(fixtureDef);

	body->SetTransform(b2Vec2((float)srp->ObjectPosition.x, (float)-srp->ObjectPosition.y), 0);

	UpdateCollisions();
}


void RigidBody::update() {
	SpriteComponent* srp = &entity->getComponent <SpriteComponent>();
	if (!isStatic) {
		position.x  = body->GetPosition().x;
		position.y  = -body->GetPosition().y;

		float radians = body->GetAngle();
		float degrees = radians * (180.0f / b2_pi);

		if (degrees < 0.0f) {
			degrees += 360.0f;
		}

		if (!FreezeX) {
			srp->ObjectPosition.x = position.x;
		}
		else {
			position.x = srp->ObjectPosition.x;
		}

		if (!FreezeY) {
			srp->ObjectPosition.y = position.y;
		}
		else {
			position.y = -srp->ObjectPosition.y;
		}

		srp->rotationAngle = degrees;
	}
	else {
		float degrees = srp->rotationAngle;
		float radians = degrees * (b2_pi / 180.0f);

		position.x = srp->ObjectPosition.x;
		position.y = -srp->ObjectPosition.y;
		body->SetTransform(b2Vec2(float(position.x), float(position.y)), radians);
	}

	//UpdateCollisions();
}


void RigidBody::draw() {

}


void RigidBody::UpdateCollisions() {
	SpriteComponent* srp = &entity->getComponent<SpriteComponent>();
	b2Vec2 localCenter(0.0f, 0.0f);
	localCenter.Set(0, 0);

	body->DestroyFixture(body->GetFixtureList());
	b2FixtureDef* fx = new b2FixtureDef();
	float scaleX = (float)srp->GlobalScale;
	float scaleY = (float)srp->GlobalScale;
	fx->density = density;
	fx->friction = friction;

	float boxWidth = srp->Scale.x * 0.5f * srp->GlobalScale;
	float boxHeight = srp->Scale.y * 0.5f * srp->GlobalScale;
	dynamicBox->SetAsBox(boxWidth, boxHeight, localCenter, 0);
	fx->shape = dynamicBox;
	fixtureDef = fx;
	body->CreateFixture(fx);

	b2MassData* mass = new b2MassData();
	mass->mass = Mass;

	body->SetMassData(mass);
	fx->shape->ComputeMass(mass, density);

	body->GetFixtureList()->SetSensor(isTrigger);

	//std::cout << "LA MASA ES " << body->GetMassData().mass << std::endl;
}



void RigidBody::clean() {
	std::cout << "Componente rigidBody removido" << std::endl;
}

void RigidBody::changeState(bool val) {
	isStatic = val;
	SpriteComponent* srp = &entity->getComponent<SpriteComponent>();
	float degrees = srp->rotationAngle;
	float radians = degrees * (b2_pi / 180.0f);

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
}


void RigidBody::triggerOn (Entity* enterEntity) {
	if (!usedTrigger) {
		std::cout << "MI OBJETO " << enterEntity->ObjectName << " ENTRO EN UNA COLISION" << std::endl;
		usedTrigger = true;
	}
}


void RigidBody::triggerOff (Entity* enterEntity) {
	if (usedTrigger) {
		std::cout << "MI OBJETO " << enterEntity->ObjectName << " SALIO DE UNA COLISION" << std::endl;
		usedTrigger = false;
	}
}