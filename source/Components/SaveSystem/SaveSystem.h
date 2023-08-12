#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "../../EngineBehaviour/GoldEngineLib.h"

using namespace std;

namespace GLD {
	class SaveSystem
	{
	public:
		static bool save(string path, string fileName, string content);
		static bool load(string path, string fileName);
	};
};