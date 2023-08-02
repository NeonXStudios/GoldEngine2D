#ifndef APPSETTINGS_H
#define APPSETTINGS_H
#include <iostream>

using namespace std;

class AppSettings
{
public:
	static AppSettings* instance;
	static int ScreenWidth;
	static int ScreenHeight;

	void create();
	void release();

	int GetWidthScreen();
	int GetHeightScreen();
};
#endif