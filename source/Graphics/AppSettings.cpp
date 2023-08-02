#include "AppSettings.h"


AppSettings* AppSettings::instance = nullptr;
int AppSettings::ScreenWidth = 1920;
int AppSettings::ScreenHeight = 1080;


void AppSettings::create() {
    if (AppSettings::instance) throw std::exception("App Settings manager already exist");
    AppSettings::instance = new AppSettings();
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