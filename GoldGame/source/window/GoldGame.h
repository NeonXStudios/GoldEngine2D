#pragma once
#include <iostream>
#include "../components/SaveData.h"
#include "../../source/EngineBehaviour/GoldEngineLib.h"
#include <filesystem>
#include <string>
#include <cstdlib>


using namespace std;

class GoldGame : public EngineBehaviour {

public:
    void start() override {
        SaveData* data = new SaveData();
        data->loadScene();
    }

    void draw() override {


    }

    void update() override {

    }

    void lateupdate() override {

    }

    void fixupdate() override {

    }

    void drawUI() override {

    }

    void release() override {

    }
};