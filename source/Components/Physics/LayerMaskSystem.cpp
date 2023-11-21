#include "LayerMaskSystem.h"

LayerMaskSystem* LayerMaskSystem::instance = nullptr;

void LayerMaskSystem::StartMaskSystem() {
	if (instance == nullptr) {
		instance = new LayerMaskSystem();
		std::cout << "Layer mask system created" << std::endl;
	}
}


void LayerMaskSystem::ClearSystem() {

}

LayerMaskSystem* LayerMaskSystem::GetSystem() {
	return instance;
}