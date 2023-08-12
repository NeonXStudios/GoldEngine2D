#include "SaveSystem.h"
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;
namespace filesystem = std::filesystem;

bool GLD::SaveSystem::save (string path, string fileName, string content) {
    std::ofstream file(path + "/" + fileName);
    std::string PathG = path;

    if (!filesystem::exists(PathG)) {
        if (!filesystem::create_directory(PathG)) {
            std::cerr << "FOLDER DONT CREATE" << endl;
            return false;
        }
    }


    if (file.is_open()) {
        file << content << std::endl;
        file.close();
        std::cout << "FILE SAVE!" << std::endl;
        return true;
    }
    else {
        std::cerr << "ERROR ON SAVE!" << std::endl;
        return false;
    }

    return false;
}


bool GLD::SaveSystem::load(string path, string fileName) {


	return false;
}