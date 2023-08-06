#ifndef APPSETTINGS_H
#define APPSETTINGS_H
#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

class AppSettings
{
public:
	static AppSettings* instance;
	static int ScreenWidth;
	static int ScreenHeight;
	static int TargetFPS;
	static int RenderWidth;
	static int RenderHeight;

	void create();
	void release();

	static void setTargetFrame (int fps);
	static int getTargetFrame ();
	static void ShowFPSConsoleDebug ();
	static void setVsyncState (int active);

	int GetWidthScreen();
	int GetHeightScreen();
};
#endif