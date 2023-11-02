//#include "Cast3D.h"
//#include "../SceneManager/SceneManager.h"
//
//bool Cast3D::RayCast (glm::vec3 RayOrigin, glm::vec3 RayDirection, float Lenght, RayCastHit* hitRay, PxHitFlags hitFlags) {
//
//	PxVec3 origin = PxVec3(RayOrigin.x, RayOrigin.y, RayOrigin.z);
//	PxVec3 dir = PxVec3 (RayDirection.x, RayDirection.y, RayDirection.z);
//
//	PxRaycastBuffer hitBuffer;
//
//
//	bool hitCasting = SceneManager::GetSceneManager()->OpenScene->mScene->raycast (origin, dir, Lenght, hitBuffer);
//
//	if (hitCasting) {
//		for (PxU32 i = 0; i < hitBuffer.getNbAnyHits(); i++) {
//			const PxRaycastHit* hit = &hitBuffer.getAnyHit(i);
//			PxShape* actor = hit->shape;
//			hitRay->point = glm::vec3 (hit->position.x, hit->position.y, hit->position.z);
//			hitRay->normal = glm::vec3(hit->normal.x, hit->normal.y, hit->normal.z);
//
//			std::string nombreDelActor = actor->getName();
//
//			hitRay->entity = SceneManager::GetSceneManager()->GetObjectByID (std::stoi (nombreDelActor));
//			return true;
//		}
//	}
//	
//	return false;
//}