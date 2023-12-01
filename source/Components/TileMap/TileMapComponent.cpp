#include "TileMapComponent.h"

void TileMapComponent::init() {
	
}


void TileMapComponent::draw() {
	for (Entity* ents : Tiles) {
		ents->draw();
	}
}

void TileMapComponent::clean() {
	for (Entity* ents : Tiles) {
		ents->ClearAllComponentes();
	}
}


void TileMapComponent::update() {
	for (Entity* ents : Tiles) {
		ents->update();
	}
}


void TileMapComponent::PreRender() {

}


void TileMapComponent::PostRender() {

}


void TileMapComponent::DeleteTile (int index) {
	if (TileSprites.size() > 0) {
		if (index >= 0 && index < TileSprites.size()) {
			TileSprites.erase(TileSprites.begin() + index);
			std::cout << "Elemento eliminado -> Quedan: " << TileSprites.size() << " tiles" << std::endl;
		}
		else {
			std::cout << "Índice fuera de rango" << std::endl;
		}
	}
}


void TileMapComponent::AddNewTile(string TilePath, glm::vec3 PositionToSet) {
	/*Entity* newTile = new Entity();
	newTile->getComponent<SpriteComponent>().TexturePath = TilePath;
	newTile->getComponent<SpriteComponent>().LoadTexture();*/
}

std::string TileMapComponent::serialize() {
	json DataToSave;
	json DataTiles = json::array();
	json Objects = json::array();

	for (int i = 0; i < TileSprites.size(); i++)
	{
		json TileData;
		TileData["PathTile"] = TileSprites[i];
		DataTiles.push_back (TileData);
	}

	DataToSave["tiles"] = DataTiles;

	for (int i = 0; i < Tiles.size(); i++) {
		json tileObject;

		tileObject["SpritePath"] = Tiles[i]->getComponent<SpriteComponent>().TexturePath;
		tileObject["posX"] = Tiles[i]->transform->Position.x;
		tileObject["posY"] = Tiles[i]->transform->Position.y;
		tileObject["posZ"] = Tiles[i]->transform->Position.z;

		tileObject["sizeX"] = Tiles[i]->transform->Scale.x;
		tileObject["sizeY"] = Tiles[i]->transform->Scale.y;

		Objects.push_back (tileObject);
	}

	DataToSave["tileObjects"] = Objects;

	return DataToSave.dump();
}


void TileMapComponent::deserialize(std::string g, std::string path) {
	json componentData = json::parse(g);
	if (CheckVar::Has(componentData, "tiles")) {

		json tilesArray = componentData["tiles"];
		json tileObjects = componentData["tileObjects"];

		for (int i = 0; i < tilesArray.size(); i++)
		{
			TileSprites.push_back (tilesArray[i]["PathTile"]);
		}

		for (int i = 0; i < tileObjects.size(); i++)
		{
			json ObjToLoad = tileObjects[i];
			Entity* newOBJ = SceneManager::GetSceneManager()->NewEntityNonSetupScene();
			newOBJ->getComponent<SpriteComponent>().TexturePath = ObjToLoad["SpritePath"];
			newOBJ->getComponent<SpriteComponent>().LoadTexture();
			newOBJ->transform->Position = glm::vec3(ObjToLoad["posX"], ObjToLoad["posY"], ObjToLoad["posZ"]);
			newOBJ->transform->Scale = glm::vec3(ObjToLoad["sizeX"], ObjToLoad["sizeY"], 1);

			Tiles.push_back (newOBJ);
		}
	}


	std::cout << "Total Tiles Loaded: " << Tiles.size() << std::endl;
}


Entity* TileMapComponent::Destroy(Entity* obj) {
	if (obj != nullptr) {
		auto it = std::find(Tiles.begin(), Tiles.end(), obj);
		if (it != Tiles.end()) {
			obj->ClearAllComponentes();
			Tiles.erase(it);
		}
	}
	return nullptr;
}