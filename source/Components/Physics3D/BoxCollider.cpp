//#include "BoxCollider.h"
//#include "nlohmann/json.hpp"
//#include <iostream>
//
//using namespace std;
//using namespace nlohmann;
//
//void BoxCollider::init() {
//	mPhysics = SceneManager::GetSceneManager()->OpenScene->mPhysics;
//	shape = mPhysics->createShape(physx::PxBoxGeometry(boxSize.x, boxSize.y, boxSize.z), *SceneManager::GetSceneManager()->OpenScene->mMaterial, 1);
//
//	string nameBODY = std::to_string(entity->objectID);
//	shape->setName (nameBODY.c_str());
//}
//
//void BoxCollider::update() {
//	shape->setName (entity->ObjectSTRID.c_str());
//
//	physx::PxGeometry* newGeometry = nullptr;
//	newGeometry = new physx::PxBoxGeometry (boxSize.x, boxSize.y, boxSize.z);
//	shape->setGeometry (*newGeometry);
//
//}
//
//void BoxCollider::draw() {
//
//}
//
//void BoxCollider::clean() {
//	shape->release();
//}
//
//std::string BoxCollider::serialize() {
//	json componentData;
//	componentData["boxsizex"] = boxSize.x;
//	componentData["boxsizey"] = boxSize.y;
//	componentData["boxsizez"] = boxSize.z;
//
//	return componentData.dump();
//}
//
//void BoxCollider::deserialize(std::string g, std::string path) {
//	json componentData = json::parse(g);
//
//	boxSize.x = componentData["boxsizex"];
//	boxSize.y = componentData["boxsizey"];
//	boxSize.z = componentData["boxsizez"];
//}
