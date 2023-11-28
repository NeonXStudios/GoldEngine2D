#include "LayerMaskSystem.h"

LayerMaskSystem* LayerMaskSystem::instance = nullptr;

void LayerMaskSystem::StartMaskSystem() {
	if (instance == nullptr) {
		instance = new LayerMaskSystem();
		std::cout << "Layer mask system created" << std::endl;

		GetSystem()->AddLayer("Default");
		GetSystem()->AddLayer("Player");
		GetSystem()->AddLayer("Ignore");
	}

	for (Mask* g : GetSystem()->GameMask)
	{
		cout << ("Layer Name: ") << g->name << endl;
	}
}


void LayerMaskSystem::ClearSystem() {

}

LayerMaskSystem* LayerMaskSystem::GetSystem() {
	return instance;
}

void LayerMaskSystem::AddLayer (string nameLayer) {
	Mask* newMask = new Mask();
	newMask->Index = GameMask.size();
	newMask->name = nameLayer;

	GameMask.push_back (newMask);
}