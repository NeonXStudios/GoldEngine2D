#pragma once
#include "../Camera/Camera2D.h"
#include "../ECS/ECS.h"
#include <vector>
#include <iostream>
#include "box2d/box2d.h"

using namespace std;


class Scene
{
public:
	Camera* worldCamera = new Camera();
	//Manager ObjectsScene;
	std::vector<Entity*> objectsInScene = std::vector<Entity*>();
	b2World* GravityWorld;

	void start();
	void update();
	void release();
	void CreateGravity();
};