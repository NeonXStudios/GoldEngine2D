#ifndef SCENE_H
#define SCENE_H


#include "../Camera/Camera2D.h"
#include "../ECS/ECS.h"
#include <vector>
#include <iostream>

using namespace std;


class Scene
{
public:
	Camera* worldCamera = new Camera();
	//Manager ObjectsScene;
	std::vector<Entity*> objectsInScene;

	void start();
	void update();
	void release();

};
#endif