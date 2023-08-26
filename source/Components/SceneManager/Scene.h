#pragma once
#include "../Camera/Camera2D.h"
#include "../ECS/ECS.h"
#include <vector>
#include <iostream>
#include "box2d/box2d.h"
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

using namespace std;

class Scene
{
public:
	Camera* worldCamera = new Camera();
	//Manager ObjectsScene;
	std::vector<Entity*> objectsInScene = std::vector<Entity*>();
	
	
	//2D CONFIGUTARION PHYSICS
	b2World* GravityWorld;


	//3D CONFIGURATION PHYSICS (PHYSX 4.1.2)
	physx::PxDefaultAllocator      mDefaultAllocatorCallback;
	physx::PxDefaultErrorCallback  mDefaultErrorCallback;
	physx::PxDefaultCpuDispatcher* mDispatcher = NULL;
	physx::PxTolerancesScale       mToleranceScale;

	physx::PxFoundation* mFoundation = NULL;
	physx::PxPhysics* mPhysics = NULL;

	physx::PxScene* mScene = NULL;
	physx::PxMaterial* mMaterial = NULL;

	physx::PxPvd* mPvd = NULL;


	void start();
	void update();
	void release();
	void CreateGravity();
};