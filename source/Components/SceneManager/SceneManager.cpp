#include "SceneManager.h"
#include "../ECS/ComponentFactory.h"
#include "../SaveSystem/SaveSystem.h"

#include <iostream>;
#include <string>
#include <vector>

using namespace std;


SceneManager* SceneManager::instance = nullptr;

void SceneManager::create()
{
	if (SceneManager::instance) throw std::exception("SceneManager already created.");
	SceneManager::instance = new SceneManager();
	std::cout << "SceneManager Created" << endl;
	SceneManager::GetSceneManager()->OpenScene = new Scene();
}



void SceneManager::release()
{
	if (!SceneManager::instance) return;
	delete SceneManager::instance;
}


SceneManager* SceneManager::GetSceneManager() {
	return instance;
}

Entity* SceneManager::NewEntity() {
	Entity* newObj = new Entity();

	/*if (&newObj->getComponent<Transform>() == nullptr) {
		newObj->addComponent<Transform>();
	}*/

	if (&newObj->getComponent<SpriteComponent>() == nullptr) {
		newObj->addComponent<SpriteComponent>();
	}

	newObj->entity = newObj;
	int objectID = OpenScene->objectsInScene.size();
	newObj->objectID = objectID;
	newObj->ObjectSTRID = std::to_string(objectID);

	std::cout << "New id: " << newObj->ObjectSTRID << std::endl;

	OpenScene->objectsInScene.push_back(newObj);
	newObj->ObjectName = "New Entity " + std::to_string(OpenScene->objectsInScene.size());

	return newObj;
}



Entity* SceneManager::GetObjectByID (int id) {
	// Asegúrate de que OpenScene y objectsInScene no sean nulos
	if (OpenScene && OpenScene->objectsInScene.size() > 0) {
		// Busca el objeto con el ID deseado en el vector de objetos de la escena
		for (Entity* obj : OpenScene->objectsInScene) {
			if (obj->objectID == id) {
				return obj; // Se encontró el objeto con el ID especificado
			}
		}
	}
	return nullptr; // No se encontró el objeto con el ID especificado o el vector estaba vacío
}

Entity* SceneManager::Destroy(Entity* obj) {
	//C++20 REQUIRE
	/*if (obj != nullptr) {
		auto it = std::ranges::find(OpenScene->objectsInScene, obj);
		if (it != OpenScene->objectsInScene.end()) {
			delete obj;
			OpenScene->objectsInScene.erase(it);
		}
	}*/

	if (obj != nullptr) {
		auto it = std::find(OpenScene->objectsInScene.begin(), OpenScene->objectsInScene.end(), obj);
		if (it != OpenScene->objectsInScene.end()) {
			delete obj;
			OpenScene->objectsInScene.erase(it);
		}
	}
	return nullptr;
}


Entity* SceneManager::GetObjectPerIndex(int index) {
	return OpenScene->objectsInScene[index];
}

Scene* SceneManager::GetOpenScene() {
	return SceneManager::GetSceneManager()->OpenScene;
}

string* SceneManager::GetOpenSceneName() {
	return &SceneManager::GetSceneManager()->OpenScene->SceneName;
}

void SceneManager::ClearOpenScene() {
	for (Entity* g : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
		g->ClearAllComponentes();
	}

	SceneManager::GetSceneManager()->OpenScene->objectsInScene.clear();
}

void SceneManager::LoadScene(string scenePath, string sceneName) {

	SceneManager::GetSceneManager()->ClearOpenScene();

	std::cout << "Scene Open: " << scenePath << sceneName << std::endl;

	SceneManager::GetSceneManager()->OpenScene->SceneName = sceneName;
	if (GLD::SaveSystem::load(scenePath/*GoldEditor::editor->ProjectPath + "/assets"*/, /*"samplescene.scene"*/sceneName).empty()) {
		std::cout << "ARCHIVO VACIO O NO EXISTENTE" << std::endl;
		return;
	}

	string loadJsonDAta = GLD::SaveSystem::load(scenePath/*GoldEditor::editor->ProjectPath + "/assets"*/, sceneName/*"samplescene.scene"*/);
	json loadJson = json::parse(loadJsonDAta);

	std::cout << "OBJETOS CARGADOS: " << loadJson["objects"].size();
	for (int i = 0; i < loadJson["objects"].size(); i++) {
		Entity* newEntity = SceneManager::GetSceneManager()->NewEntity();
		json getEntityData = loadJson["objects"][i];
		newEntity->ObjectName = getEntityData["name"];
		newEntity->ObjectTag = getEntityData["tag"];
		newEntity->transform->deserialize(getEntityData["transform"], "");


		std::vector<Component*> cmpms = newEntity->getComponents<Component>();

		for (int e = 0; e < cmpms.size(); e++) {
			json cpmOBJ;
			Component* selectComponent = cmpms[e];
			string typeg = typeid(*selectComponent).name();

			std::string newName = typeg;
			size_t pos = newName.find("class ");
			if (pos != std::string::npos) {
				newName.replace(pos, 6, "");
			}

			for (int j = 0; j < getEntityData["components"].size(); j++) {
				json getComponent = getEntityData["components"][j];


				//if (getComponent["componenttype"] == newName) {
				//    selectComponent->deserialize (getComponent["componentdata"].dump());
				//}

				ComponentFactory::loadComponent(getComponent["componenttype"].dump(), newEntity, getComponent["componentdata"].dump(), "");
			}
		}
	}
}