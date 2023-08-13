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
		static string load(string path, string fileName);
		static bool fileExists(const std::string& filename);
	};
};