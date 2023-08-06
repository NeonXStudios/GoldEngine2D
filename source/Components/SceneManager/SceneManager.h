#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"


class SceneManager
{
public:
	static SceneManager* instance;
	Scene* OpenScene = new Scene();
	static void create();
	static void release();

	static SceneManager* GetSceneManager();
	Entity* NewEntity	  ();
	Entity* GetObjectByID (int id);
};
#endif