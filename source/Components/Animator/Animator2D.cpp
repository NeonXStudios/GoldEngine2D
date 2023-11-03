#include "Animator2D.h"



void Animator2D::NextFrame(float wtT) {
    while (true) {
        states[SelectState]->cp = cp;
        states[SelectState]->UpdateState();
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(wtT * 1000)));
    }
}

void Animator2D::init() {
    cp = &entity->getComponent<SpriteComponent>();

    AnimationsStates* newState = new AnimationsStates();
    newState->StateName = "Idle";
    states.push_back (newState);

    AddNewState("Idle");
    float wtT = NextFrameTime;

    std::thread t([this, wtT]() {
        NextFrame(wtT);
    });

    t.detach();
}


void Animator2D::update() {

}


void Animator2D::draw() {

}


void Animator2D::clean() {

}

void Animator2D::AddNewState (string StateName) {

    for (AnimationsStates* SelectState : states) {
        if (SelectState->StateName == StateName) {
            SelectState->AddNewFrame("playersprites/idle/Warrior_Idle_1.png");
            SelectState->AddNewFrame("playersprites/idle/Warrior_Idle_2.png");
            SelectState->AddNewFrame("playersprites/idle/Warrior_Idle_3.png");
            SelectState->AddNewFrame("playersprites/idle/Warrior_Idle_4.png");
            SelectState->AddNewFrame("playersprites/idle/Warrior_Idle_5.png");
            SelectState->AddNewFrame("playersprites/idle/Warrior_Idle_6.png");
        } 
    }
}


string Animator2D::serialize() {

    return "";
}


void Animator2D::deserialize(std::string g, std::string path) {

}