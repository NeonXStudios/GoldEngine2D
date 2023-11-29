#pragma once
#include "../ECS/ECS.h"
#include "../../RequireLibs.h"
#include "../Sprite/SpriteComponent.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

class TileMapComponent : public Component
{
public:
	std::vector<string> TileSprites = std::vector<string>();
	std::vector<Entity*> Tiles = std::vector<Entity*>();
	

	void init() override;
	void draw() override;
	void clean() override;
	void update() override;
	void PreRender() override;
	void PostRender() override;
	std::string serialize() override;
	void deserialize(std::string g, std::string path = "") override;

	
	void AddNewTile(string TilePath, glm::vec3 PositionToSet);
};