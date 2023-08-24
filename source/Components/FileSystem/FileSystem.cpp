#include "FileSystem.h"
#include "../../Graphics/StartEngineGraphics.h"
#include "../../Graphics/AppSettings.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string FileSystem::GetAsset(string FilePath) {

	if (!AppSettings::gameRunning) {
		std::string output = StartEngineGraphics::instance->engine->GamePath + "\\assets\\" + FilePath;
		std::replace(output.begin(), output.end(), '\\', '/');
		return output;

	}
	else {
		std::string output = StartEngineGraphics::instance->engine->GamePath + "\\assets\\" + FilePath;
		std::replace (output.begin(), output.end(), '\\', '/');


		std::string::size_type pos = output.find("assets");
		if (pos != std::string::npos) {
			output.replace(pos, 6, "/");
		}

		string newPath = "game/" + output;
		return newPath;
	}

	return "RETURN NULL";
}