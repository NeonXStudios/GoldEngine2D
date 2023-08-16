#include "AppSettings.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;

AppSettings* AppSettings::instance = nullptr;
int AppSettings::ScreenWidth = 1920;
int AppSettings::ScreenHeight = 1080;
int AppSettings::RenderWidth = 0;
int AppSettings::RenderHeight = 0;

int AppSettings::TargetFPS = 30;
bool AppSettings::gameRunning = false;


void AppSettings::create() {
    if (AppSettings::instance) throw std::exception("App Settings manager already exist");
    AppSettings::instance = this;
    std::cout << "APP SETTINGS CREATED..." << endl;
    
    //std::ifstream file("gamedata.json");
    //if (!file.is_open()) {
    //    std::cerr << "No se pudo abrir el archivo." << std::endl;
    //}

    //// Leer el contenido del archivo
    //nlohmann::json json_data;
    //try {
    //    file >> json_data;
    //}
    //catch (const nlohmann::json::parse_error& e) {
    //    std::cerr << "Error al analizar el archivo JSON: " << e.what() << std::endl;
    //}

    //RunningGame = (bool)json_data["gameRun"];
}

void AppSettings::release() {
    if (!AppSettings::instance) return;
    delete AppSettings::instance;
}

int AppSettings::GetWidthScreen() {
    return ScreenWidth;
}


int AppSettings::GetHeightScreen() {
    return ScreenHeight;
}

void AppSettings::setTargetFrame (int fps) {
    TargetFPS = fps;
}

int AppSettings::getTargetFrame() {
    return TargetFPS;
}

void AppSettings::setVsyncState (int active) {
    glfwWindowHint(GLFW_DOUBLEBUFFER, active);
}