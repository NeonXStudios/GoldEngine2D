#pragma once
#include <iostream>
#include "../../EngineBehaviour/GoldEngineLib.h"

using namespace std;

class SaveSystem
{
	bool save (string path, string fileName);
	bool load (string path, string fileName);
};