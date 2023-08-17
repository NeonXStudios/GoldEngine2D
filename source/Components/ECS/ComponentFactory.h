#pragma once
#include "../../EngineBehaviour/GoldEngineLib.h"

class ComponentFactory
{
public:
	static void loadComponent (string ComponentName, Entity* owner, string data, std::string path = "") {
		std::string componentName = ComponentName.substr(1, ComponentName.size() - 2);

		if (componentName == "SpriteComponent") {
			SpriteComponent* g = &owner->getComponent<SpriteComponent>();
			g->deserialize (data, path);
		}

		if (componentName == "AudioSource") {
			AudioSource* g = &owner->addComponent<AudioSource>();
			g->deserialize (data, path);
		}

		if (componentName == "RigidBody") {
			RigidBody* g = &owner->addComponent<RigidBody>();
			g->deserialize (data, path);
		}

		if (componentName == "ScriptCompiler") {
			ScriptCompiler* g = &owner->addComponent<ScriptCompiler>();
			g->deserialize (data, path);
		}
	}
};