#include <iostream>
#include "../../../source/EngineBehaviour/GoldEngineLib.h"
//#include "../UI/UIManager.h"

class GoldEditor : public EngineBehaviour { 
public:
    static GoldEditor* editor;
    //UIManager* uiMaster = new UIManager();

    void start() override {
        //uiMaster->start();
        std::cout << "Starting editor" << endl;
    }

    void draw() override {

    }

    void update() override {
        //uiMaster->update();
    }

    void lateupdate() override {
        //uiMaster->lateupdate();
    }

    void fixupdate() override {
        //uiMaster->fixupdate();
    }

    void drawUI() override {
        //uiMaster->draw();
    }

    void release() override {
       
    }
};

