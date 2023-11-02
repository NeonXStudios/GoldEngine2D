//#include "Rigidbody3d.h"
//#include "nlohmann/json.hpp"
//#include <cmath>
//# define M_PI           3.14159
//
//using namespace nlohmann;
//
//void Rigidbody3d::init() {
//	if (SceneManager::GetSceneManager() != nullptr) {
//		if (SceneManager::GetSceneManager()->OpenScene->mPhysics == nullptr) {
//			std::cout << "PARECE QUE LAS FISICAS NO EXISTEN " << std::endl;
//			return;
//		}
//
//		if (SceneManager::GetSceneManager()->OpenScene->mMaterial == nullptr) {
//			std::cout << "EL MATERIAL ES NULL" << std::endl;
//			throw ("MATERIAL NULL ERROR ON CREATE RIGID BODY 3D");
//			return;
//		}
//
//		mPhysics = SceneManager::GetSceneManager()->OpenScene->mPhysics;
//
//		//shape = mPhysics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *SceneManager::GetSceneManager()->OpenScene->mMaterial, 1);
//		physx::PxTransform t(physx::PxVec3(0));
//
//		// Crear un objeto dinámico
//		body = mPhysics->createRigidDynamic(t);
//
//		string nameBODY = std::to_string(entity->objectID);
//		body->setName(nameBODY.c_str());
//
//		//body->attachShape(*shape);
//		physx::PxRigidBodyExt::updateMassAndInertia(*body, mass);
//		SceneManager::GetSceneManager()->OpenScene->mScene->addActor(*body);
//
//		body->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, isStatic);
//		body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !useGravity);
//
//		body->wakeUp();
//
//		//shape->release();
//	}
//	else {
//		std::cout << "Parece que el SceneManager no existe!" << std::endl;
//	}
//
//	if (body != nullptr) {
//		body->setGlobalPose(PxTransform(entity->transform->Position.x, entity->transform->Position.y, entity->transform->Position.z));
//		PxQuat newRotation(PxPi / 4.0f, PxVec3(entity->transform->Rotation.x, entity->transform->Rotation.y, entity->transform->Rotation.z)); // Rotación de 45 grados alrededor del eje Y
//		//body->setGlobalPose(PxTransform(body->getGlobalPose().p, newRotation), true);
//	}
//}
//
//void Rigidbody3d::update() {
//	string nameBODY = std::to_string(entity->objectID);
//	body->setName(nameBODY.c_str());
//
//	if (body != nullptr) {	
//		physx::PxTransform pose = body->getGlobalPose();
//		physx::PxVec3 position = pose.p;
//		physx::PxQuat rotation = body->getGlobalPose().q;
//
//		physx::PxRigidBodyExt::updateMassAndInertia(*body, mass);
//		
//		entity->transform->Position = glm::vec3(
//			position.x, 
//			position.y, 
//			position.z
//		);
//
//		double gradosX = rotation.x * (180.0 / M_PI);
//		double gradosY = rotation.y * (180.0 / M_PI);
//		double gradosZ = rotation.z * (180.0 / M_PI);
//
//		entity->transform->Rotation.x = gradosX;
//		entity->transform->Rotation.y = gradosY;
//		entity->transform->Rotation.z = gradosZ;
//
//
//		body->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, isStatic);
//		body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !useGravity);
//
//
//
//		if (entity != nullptr) { 
//			if (&entity->getComponent <BoxCollider>() && !shapeAttached) {
//			     body->attachShape (*entity->getComponent<BoxCollider>().shape);
//				 shapeAttached = true;
//			}
//		}
//
//		if (isStatic) {
//			waked = false;
//		}
//
//		if (!waked && !isStatic) {
//			body->wakeUp();
//			waked = true;
//		}
//	}
//}
//
//void Rigidbody3d::draw() {
//
//}
//
//void Rigidbody3d::clean() {
//
//}
//
//std::string Rigidbody3d::serialize() {
//	json componentData;
//	componentData["friction"] = friction;
//	componentData["mass"] = mass;
//	componentData["drag"] = drag;
//	componentData["angularDrag"] = angularDrag;
//	componentData["automaticCenterOfMass"] = automaticCenterOfMass;
//	componentData["automaticSensor"] = automaticSensor;
//	componentData["useGravity"] = useGravity;
//	componentData["isStatic"] = isStatic;
//
//	componentData["freezePosX"] = freezePosX;
//	componentData["freezePosY"] = freezePosY;
//	componentData["freezePosZ"] = freezePosZ;
//
//	componentData["freezeRotX"] = freezeRotX;
//	componentData["freezeRotY"] = freezeRotY;
//	componentData["freezeRotZ"] = freezeRotZ;
//
//	return componentData.dump();
//}
//
//void Rigidbody3d::deserialize(std::string g, std::string path) {
//	json componentData = json::parse(g);
//	friction = componentData["friction"];
//	mass = componentData["mass"];
//	drag = componentData["drag"];
//	angularDrag = componentData["angularDrag"];
//	automaticCenterOfMass = componentData["automaticCenterOfMass"];
//	automaticSensor = componentData["automaticSensor"];
//	useGravity = componentData["useGravity"];
//	isStatic = componentData["isStatic"];
//
//	freezePosX = componentData["freezePosX"];
//	freezePosY = componentData["freezePosY"];
//	freezePosZ = componentData["freezePosZ"];
//
//	freezeRotX = componentData["freezeRotX"];
//	freezeRotY = componentData["freezeRotY"];
//	freezeRotZ = componentData["freezeRotZ"];
//}