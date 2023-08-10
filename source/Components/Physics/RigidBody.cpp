#include "RigidBody.h"



void RigidBody::init() {
	SpriteComponent* srp = &entity->getComponent <SpriteComponent>();

	if (dynamicBox == nullptr) {
		dynamicBox = new b2PolygonShape();
	}
	if (fixtureDef == nullptr) {
		fixtureDef = new b2FixtureDef();
	}

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
	//Object::UpdateBody();
	body->SetTransform(b2Vec2((float)0, (float)0), 0);
}




void RigidBody::update() {
	SpriteComponent* srp = &entity->getComponent <SpriteComponent>();
	if (!isStatic) {
		position.x  = body->GetPosition().x;
		position.y  = -body->GetPosition().y;
		srp->ObjectPosition.x = position.x;
		srp->ObjectPosition.y = position.y;
		float radians = body->GetAngle();  // Obtén la rotación en radianes desde Box2D
		float degrees = radians * (180.0f / b2_pi);  // Convertir a grados

		if (degrees < 0.0f) {
			degrees += 360.0f;  // Asegurar que el ángulo esté en el rango 0-360
		}
		srp->rotationAngle = degrees;
	}
	else {
		float degrees = srp->rotationAngle;
		float radians = degrees * (b2_pi / 180.0f);

		position.x = srp->ObjectPosition.x;
		position.y = -srp->ObjectPosition.y;
		body->SetTransform(b2Vec2(float(position.x), float(position.x)), radians);
	}

	UpdateCollisions();
}


void RigidBody::UpdateCollisions() {
	SpriteComponent* srp = &entity->getComponent <SpriteComponent>();
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
}


void RigidBody::draw() {

}




void RigidBody::clean() {

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
	}
}