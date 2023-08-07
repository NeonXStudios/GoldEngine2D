#include "HUDS/SceneUI.h"
#include "HUDS/BarMenuUI.h"
#include "HUDS/HierarchyUI.h"

class UIManager {
public:
	SceneUI* sceneui = new SceneUI();
	BarMenuUI* mainmenuui = new BarMenuUI();
	HierarchyUI* hierarhcyui = new HierarchyUI();

	void start() {
		sceneui->start();
	}

	void draw() {
		sceneui->draw();
		mainmenuui->draw();
		hierarhcyui->draw();
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