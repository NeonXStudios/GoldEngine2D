#pragma once
#include "HUDS/SceneUI.h"
#include "HUDS/BarMenuUI.h"
#include "HUDS/HierarchyUI.h"
#include "HUDS/Assets.h"
#include "HUDS/Inspector.h"

class UIManager {
public:
	static UIManager* instance;

	SceneUI* sceneui = new SceneUI();
	BarMenuUI* mainmenuui = new BarMenuUI();
	HierarchyUI* hierarhcyui = new HierarchyUI();
	InspectorUI* inspectorui = new InspectorUI();
	AssetsUI* assetsui = new AssetsUI();


	void start() {
		instance = new UIManager();
		sceneui->start();
		assetsui->start();
	}

	void draw() {
		sceneui->draw();
		mainmenuui->draw();
		hierarhcyui->draw();
		assetsui->draw();
		inspectorui->draw();
	}

	void update() {
		sceneui->update();
	}

	void fixupdate() {
		sceneui->fixupdate();
	}

	void lateupdate() {
		sceneui->lateupdate();
	}
};