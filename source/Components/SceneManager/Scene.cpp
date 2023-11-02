#include "Scene.h"
#include "../Sprite/SpriteComponent.h"
#include "../AudioSource/AudioSource.h"
#include "../Physics/TriggerModule.h"
#include "../../source/Graphics/AppSettings.h"

void Scene::start() {
	CreateGravity();

	//worldCamera = new Camera (AppSettings::ScreenWidth, AppSettings::ScreenHeight, glm::vec3(0.0f, 0.0f, 2.0f));
	worldCamera->start();
}

void Scene::update() {
	//worldCamera->Inputs(StartEngineGraphics::window);
	//worldCamera->updateMatrix(45.0f, 0.1f, 1000.0f);
	worldCamera->update();

	for (Entity* ents : objectsInScene) {
		//ents->entity = ents;
		ents->update();
	}


	if (AppSettings::gameRunning) {
		if (GravityWorld != nullptr && GravityWorld->GetBodyCount() > 0) {

			b2Body* body = GravityWorld->GetBodyList();
			float timeStep = 1.0f / 60;
			GravityWorld->Step(timeStep, 6, 2);
			body->GetNext();
		}

	}

		//mScene->simulate(1.0f / 60.0f);
		//mScene->fetchResults(true);
}

void Scene::draw() {
	for (Entity* ents : objectsInScene) {
		//ents->entity = ents;
		ents->draw();
	}
}

void Scene::PreRender() {
	for (Entity* ents : objectsInScene) {
		//ents->entity = ents;
		ents->PreRender();
	}
}

void Scene::PostRender() {
	for (Entity* ents : objectsInScene) {
		//ents->entity = ents;
		ents->PostRender();
	}
}

void Scene::release() {

}


void Scene::CreateGravity() {
#pragma region CREATE PHYSICS 2D
	b2Vec2 gravity(0, 20);
	GravityWorld = new b2World(gravity);

	if (GravityWorld != nullptr) {
		//TriggerData* data = new TriggerData();
		TriggerModule* triggerData = new TriggerModule();
		GravityWorld->SetContactListener(triggerData);
		std::cout << "Gravity created " << endl;
	}
#pragma endregion

//#pragma region CREATE PHYSICS 3D PHYSX 4.1.2
//	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
//	if (!mFoundation) throw("PxCreateFoundation failed!");
//	mPvd = PxCreatePvd(*mFoundation);
//	physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
//	mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
//	//mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(),true, mPvd);
//	mToleranceScale.length = 100;        // typical length of an object
//	mToleranceScale.speed = 981;         // typical speed of an object, gravity*1s is a reasonable choice
//	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
//	//mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale);
//
//	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
//	sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
//	mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
//	sceneDesc.cpuDispatcher = mDispatcher;
//	sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
//	mScene = mPhysics->createScene(sceneDesc);
//
//	physx::PxPvdSceneClient* pvdClient = mScene->getScenePvdClient();
//	if (pvdClient)
//	{
//		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
//		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
//		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
//	}
//
//	// create simulation
//	mMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);
//#pragma endregion
}