#include "TileMapComponent.h"

void TileMapComponent::init() {

}


void TileMapComponent::draw() {

}

void TileMapComponent::clean() {

}


void TileMapComponent::update() {

}


void TileMapComponent::PreRender() {

}


void TileMapComponent::PostRender() {

}



void TileMapComponent::AddNewTile(string TilePath, glm::vec3 PositionToSet) {
	/*Entity* newTile = new Entity();
	newTile->getComponent<SpriteComponent>().TexturePath = TilePath;
	newTile->getComponent<SpriteComponent>().LoadTexture();*/
}

std::string TileMapComponent::serialize() {
	json DataToSave;
	DataToSave["tiles"] = "NULL";

	return DataToSave.dump();
}


void TileMapComponent::deserialize(std::string g, std::string path) {

}