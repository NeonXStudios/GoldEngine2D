#pragma once
#include "../../source/EngineBehaviour/GoldEngineLib.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "nlohmann/json.hpp"

using namespace std;

class SaveData
{
	public:
	//static string CurrentOpenScene;
	static void saveScene ();
	static void loadScene ();
};