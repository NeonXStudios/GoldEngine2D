#include "UIManager.h"

UIManager* UIManager::instance = nullptr;

void UIManager::start (){
	UIManager::instance = this;
	sceneui = new SceneUI();
	mainmenuui = new BarMenuUI();
	hierarhcyui = new HierarchyUI();
	inspectorui = new InspectorUI();
	assetsui = new AssetsUI();
	rightClickui = new RightClickUI();


	inspectorui->start();
	sceneui->start();
	assetsui->start();
}

void UIManager::draw() {
	sceneui->draw();
	mainmenuui->draw();
	hierarhcyui->draw();
	assetsui->draw();
	inspectorui->draw();
	rightClickui->draw();

	if (editorScript != nullptr) {
		editorScript->update();
	}
}

void UIManager::update() {
	sceneui->update();
	inspectorui->update();
}

void UIManager::fixupdate() {
	sceneui->fixupdate();
}

void UIManager::lateupdate() {
	sceneui->lateupdate();
}

void UIManager::createScriptEditor (Entity* owner) {
	editorScript = new ScriptEditor (owner);
}

UIManager::~UIManager() {
	delete sceneui;
	delete mainmenuui;
	delete hierarhcyui;
	delete inspectorui;
	delete assetsui;
}