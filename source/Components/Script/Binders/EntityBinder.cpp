#include "EntityBinder.h"

using namespace glm;

void EntityBinder::RegisterFunctions(ScriptCompiler* luaParent)
{
	luaParent->lua["self"] = sol::make_object(luaParent->lua.lua_state(), luaParent->entity);
	luaParent->lua.new_usertype<Entity>("Object",
		"name", &Entity::ObjectName,
		"tag", &Entity::ObjectTag,


		//GET COMPONENTS
		"GetTransform", &Entity::getComponent<SpriteComponent>,
		"GetRigidBody", &Entity::getComponent<RigidBody>,
		"GetAudioSource", &Entity::getComponent<AudioSource>
	);

	luaParent->lua.new_usertype<RigidBody>("RigidBody",
		"static", &RigidBody::isStatic,
		"freezeX", &RigidBody::FreezeX,
		"freezeY", &RigidBody::FreezeY,
		"density", &RigidBody::density,
		"friction", &RigidBody::friction,
		"isTrigger", &RigidBody::isTrigger,
		"addForce", &RigidBody::addForce
	);


	luaParent->lua.new_usertype<AudioSource>("AudioSource",
		"volumen", &AudioSource::SetVolumen,
		"getVolumen", &AudioSource::GetVolumen,
		"pan", &AudioSource::SetPan,
		"getPan", &AudioSource::GetPan,
		"stop", &AudioSource::Stop,
		"reset", &AudioSource::Reset,
		"isPlaying", &AudioSource::IsPlaying,
		"audio", &AudioSource::AudioPath
	);

	luaParent->lua.new_usertype<SpriteComponent>("SpriteComponent",
		"position", &SpriteComponent::ObjectPosition,
		"scale", &SpriteComponent::Scale,
		"gScale", &SpriteComponent::GlobalScale,
		"rotation", &SpriteComponent::rotationAngle,
		"texture", &SpriteComponent::TexturePath
	);
}