#include "HUDS/SceneUI.h"


class UIManager {
	SceneUI* sceneui = new SceneUI();

public:
	void start() {
		sceneui->start();
	}

	void draw() {
		sceneui->draw();
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