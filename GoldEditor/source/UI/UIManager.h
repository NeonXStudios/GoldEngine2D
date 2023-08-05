#include "HUDS/SceneUI.h"
#include "HUDS/BarMenuUI.h"


class UIManager {
public:
	SceneUI* sceneui = new SceneUI();
	BarMenuUI* mainmenuui = new BarMenuUI();

	void start() {
		sceneui->start();
	}

	void draw() {
		sceneui->draw();
		mainmenuui->draw();
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