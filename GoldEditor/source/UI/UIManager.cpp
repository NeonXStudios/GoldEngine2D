#include "UIManager.h"
//
//#define IMGUI_DEFINE_MATH_OPERATORS
//#include <imguinode/imgui_node_editor.h>

UIManager* UIManager::instance = nullptr;

//namespace ed = ax::NodeEditor;
//ed::EditorContext* m_Context = nullptr;

void UIManager::start (){
	UIManager::instance = this;
	sceneui = new SceneUI();
	mainmenuui = new BarMenuUI();
	hierarhcyui = new HierarchyUI();
	inspectorui = new InspectorUI();
	assetsui = new AssetsUI();
	rightClickui = new RightClickUI();
	cameraSettingUI = new CameraSetting();

	inspectorui->start();
	sceneui->start();
	assetsui->start();

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

	if (editorScript != nullptr) {
		editorScript->update();
	}
}

void UIManager::update() {
	sceneui->update();
	inspectorui->update();

	auto& io = ImGui::GetIO();

	//ImGui::Text("FPS: %.2f (%.2gms)", io.Framerate, io.Framerate ? 1000.0f / io.Framerate : 0.0f);

	//ImGui::Separator();

	//ed::SetCurrentEditor(m_Context);
	//ed::Begin("My Editor", ImVec2(0.0, 0.0f));
	//int uniqueId = 1;
	//// Start drawing nodes.
	//ed::BeginNode(uniqueId++);
	//ImGui::Text("Node A");
	//ed::BeginPin(uniqueId++, ed::PinKind::Input);
	//ImGui::Text("-> In");
	//ed::EndPin();
	//ImGui::SameLine();
	//ed::BeginPin(uniqueId++, ed::PinKind::Output);
	//ImGui::Text("Out ->");
	//ed::EndPin();
	//ed::EndNode();
	//ed::End();
	//ed::SetCurrentEditor(nullptr);
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