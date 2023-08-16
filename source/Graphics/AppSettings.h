#pragma once
#include <iostream>
#include "../RequireLibs.h"

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
	
	static bool gameRunning;

	void create();
	void release();

	static void setTargetFrame (int fps);
	static int getTargetFrame ();
	static void setVsyncState (int active);

	int GetWidthScreen();
	int GetHeightScreen();
};