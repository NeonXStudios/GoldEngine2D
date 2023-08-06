#include <iostream>
#include "../../../source/EngineBehaviour/GoldEngineLib.h"
#include "../UI/UIManager.h"

Entity* player;
Entity* player2;
Entity* player3;
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

        player3 = SceneManager::GetSceneManager()->NewEntity();
        player3->ObjectTag = "OBJETO3";
        player3->addComponent<SpriteComponent>();

        player3->getComponent<SpriteComponent>().cubePosition = glm::vec3(0, 500, 0);
        box->start();
    }

    void draw() override {
        box->draw();
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

