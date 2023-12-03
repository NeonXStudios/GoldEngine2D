#include "EntityBinder.h"

using namespace glm;

void EntityBinder::RegisterFunctions(ScriptCompiler* luaParent)
{
	luaParent->lua["self"] = sol::make_object(luaParent->lua.lua_state(), luaParent->entity);

	luaParent->lua.new_usertype<Entity>("Object",
		"name", &Entity::ObjectName,
		"tag", &Entity::ObjectTag,

		//GET COMPONENTS
		"transform", &Entity::transform,
		"GetRigidBody", &Entity::getComponent<RigidBody>,
		"GetAudioSource", &Entity::getComponent<AudioSource>,
		"GetAnimator", & Entity::getComponent<Animator2D>,
		"GetTileMap", &Entity::getComponent<TileMapComponent>,
		"GetSprite", &Entity::getComponent<SpriteComponent>,
		"GetMaterial", &Entity::getComponent<MaterialComponent>
	);

	luaParent->lua["Scene"] = sol::make_object(luaParent->lua.lua_state(), SceneManager::GetSceneManager());
	luaParent->lua.new_usertype<SceneManager>("SceneManager",
		"GetObjectPerID", &SceneManager::GetObjectPerIndex,
		"ChangeScene", &SceneManager::LoadScene,
		"newEntity", &SceneManager::NewEntity,
		"Destroy", &SceneManager::Destroy
	);

	luaParent->lua.new_usertype<RigidBody>("RigidBody",
		"static", &RigidBody::isStatic,
		"freezeX", &RigidBody::FreezeX,
		"freezeY", &RigidBody::FreezeY,
		"density", &RigidBody::density,
		"friction", &RigidBody::friction,
		"isTrigger", &RigidBody::isTrigger,
		"addForce", &RigidBody::addForce,
		"mass", &RigidBody::Mass,
		"density", &RigidBody::density,
		"friction", &RigidBody::friction
	);

	luaParent->lua.new_usertype<AudioSource>("AudioSource",
		"volumen", &AudioSource::SetVolumen,
		"getVolumen", &AudioSource::GetVolumen,
		"pan", &AudioSource::SetPan,
		"getPan", &AudioSource::GetPan,
		"stop", &AudioSource::Stop,
		"reset", &AudioSource::Reset,
		"isPlaying", &AudioSource::IsPlaying,
		"audio", &AudioSource::AudioPath,
		"minDistance", &AudioSource::minDistance,
		"maxDistance", &AudioSource::maxDistance
	);

	luaParent->lua.new_usertype<Animator2D>("Animator", 
		"setState", &Animator2D::SetState,
		"getState", &Animator2D::GetCurrentState
	);


	luaParent->lua.new_usertype<SpriteComponent>("SpriteComponent",
		"reloadTexture", &SpriteComponent::LoadTexture
	);

	luaParent->lua.new_usertype<MaterialComponent>("Material",
		"setBool", &MaterialComponent::setBool,
		"setInt", &MaterialComponent::setInt,
		"setFloat", &MaterialComponent::setFloat,
		"setVec2", &MaterialComponent::setVec2,
		"setVec3", &MaterialComponent::setVec3,
		"setVec4", &MaterialComponent::setVec4,
		"setMat2", &MaterialComponent::setMat2,
		"setMat3", &MaterialComponent::setMat3,
		"setMat4", &MaterialComponent::setMat4
	);
}