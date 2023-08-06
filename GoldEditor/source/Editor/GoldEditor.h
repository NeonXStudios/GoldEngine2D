#include <iostream>
#include "../../../source/EngineBehaviour/GoldEngineLib.h"
#include "../UI/UIManager.h"

Entity* player;
Entity* player2;
UIManager* uiMaster = new UIManager();


class GoldEditor : public EngineBehaviour { 
public:
    static GoldEditor* editor;

    void start() override {
        uiMaster->start();
        std::cout << "Starting editor" << endl;



        player = SceneManager::GetSceneManager()->NewEntity();
        player->ObjectTag = "OBJETO1";
        player->addComponent<SpriteComponent>();


        player2 = SceneManager::GetSceneManager()->NewEntity();
        player2->ObjectTag = "OBJETO2";
        player2->addComponent<SpriteComponent>();

        player2->getComponent<SpriteComponent>().cubePosition = glm::vec3 (25, 25, 0);
    }

    void draw() override {
        
    }

    void update() override {
        uiMaster->update();
    }

    void lateupdate() override {
        uiMaster->lateupdate();
    }

    void fixupdate() override {
        uiMaster->fixupdate();
    }

    void drawUI() override {
        uiMaster->draw();
    }

    void release() override {
       
    }
};

