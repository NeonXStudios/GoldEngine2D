#pragma once
#include "Scene.h"
#include "../../Components/Sprite/SpriteComponent.h"


class SceneManager
{
public:
	Scene* OpenScene;
	static SceneManager* instance;
	static void create();
	static void release();

	static SceneManager* GetSceneManager();
	Entity* NewEntity	  ();
	Entity* GetObjectByID (int id);
	Entity* Destroy (Entity* object);
};