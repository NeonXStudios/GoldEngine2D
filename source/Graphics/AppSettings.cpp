#include "AppSettings.h"


AppSettings* AppSettings::instance = nullptr;
int AppSettings::ScreenWidth = 1920;
int AppSettings::ScreenHeight = 1080;
int AppSettings::RenderWidth = 0;
int AppSettings::RenderHeight = 0;

int AppSettings::TargetFPS = 30;


void AppSettings::create() {
    if (AppSettings::instance) throw std::exception("App Settings manager already exist");
    AppSettings::instance = this;
    std::cout << "APP SETTINGS CREATED..." << endl;
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