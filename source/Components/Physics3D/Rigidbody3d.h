#pragma once
#include "../../EngineBehaviour/GoldEngineLib.h"
#include <iostream> 

using namespace std;
using namespace nlohmann;
using namespace physx;

class Rigidbody3d : public Component{
public:
	float mass = 1;
	float drag = 0;
	float angularDrag = 0.05f;
	bool automaticCenterOfMass = true;
	bool automaticSensor = true;

	float friction = 0.5f;
	
	bool isStatic;
	bool useGravity;

	bool freezePosX = false;
	bool freezePosY = false;
	bool freezePosZ = false;

	bool freezeRotX = false;
	bool freezeRotY = false;
	bool freezeRotZ = false;

	bool shapeAttached;
	
	physx::PxRigidDynamic* body;
	physx::PxMaterial* mMaterial = NULL;
	physx::PxPhysics* mPhysics = NULL;


	bool waked;


	void init() override;

	void update() override;

	void draw() override;

	void clean() override;

	std::string serialize() override;

	void deserialize(std::string g, std::string path = "") override;
};