#include "Animator2D.h"



void Animator2D::NextFrame(float wtT) {
    while (true) {
        for (AnimationsStates* stateFound : states) {
            if (stateFound->StateName == SelectState) {
                stateFound->cp = cp;
                stateFound->UpdateState();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(wtT * 1000)));
    }
}

void Animator2D::init() {
    cp = &entity->getComponent<SpriteComponent>();



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
    AnimationsStates* newState = new AnimationsStates();
    newState->StateName = StateName;
    states.push_back(newState);
}

void Animator2D::RebuildAnimator() {
    for (AnimationsStates* stateSelect : states) {
        stateSelect->RebuildState();
    }
}


string Animator2D::serialize() {

    return "{}";
}


void Animator2D::deserialize(std::string g, std::string path) {

}