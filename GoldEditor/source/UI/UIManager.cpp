#include "UIManager.h"


UIManager* UIManager::instance = nullptr;


void UIManager::start (){
	UIManager::instance = this;
	sceneui = new SceneUI();
	mainmenuui = new BarMenuUI();
	hierarhcyui = new HierarchyUI();
	inspectorui = new InspectorUI();
	assetsui = new AssetsUI();


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

UIManager::~UIManager() {
	delete sceneui;
	delete mainmenuui;
	delete hierarhcyui;
	delete inspectorui;
	delete assetsui;
}