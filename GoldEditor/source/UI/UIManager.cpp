#include "UIManager.h"


//SINGLETON VARIABLE
UIManager* UIManager::instance = nullptr;


void UIManager::start (){
	UIManager::instance = this;
	sceneui = new SceneUI();
	mainmenuui = new BarMenuUI();
	hierarhcyui = new HierarchyUI();
	inspectorui = new InspectorUI();
	assetsui = new AssetsUI();
	rightClickui = new RightClickUI();
	cameraSettingUI = new CameraSetting();
	nodePanel = new NodeUI();

	inspectorui->start();
	sceneui->start();
	assetsui->start();
	nodePanel->start();

	//ed::Config config;
	//config.SettingsFile = "Simple.json";
	//m_Context = ed::CreateEditor(&config);
}

void UIManager::draw() {
	ImGui::DockSpaceOverViewport();

	sceneui->draw();
	mainmenuui->draw();
	hierarhcyui->draw();
	assetsui->draw();
	inspectorui->draw();
	rightClickui->draw();
	cameraSettingUI->draw();
	nodePanel->update();

	if (editorScript != nullptr) {
		editorScript->update();
	}
}

void UIManager::update() {
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