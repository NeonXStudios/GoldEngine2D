#include "FileSystem.h"

using namespace std;

string FileSystem::readFile(string path) {
	std::ifstream fileG (path);


	if (!fileG.is_open()) {
		std::cerr << "ERROR ON TRY OPEN THE FILE!" << std::endl;
		return "ERROR ON TRY OPEN THE FILE!";
	}

	std::string line;


	std::string content ((std::istreambuf_iterator <char>(fileG)), std::istreambuf_iterator<char>());


	std::cout << "DATA FOUND!" << std::endl;

	if (!content.empty()) {
		return content;
	}

	fileG.close();


	return "FILE NOT FOUND!";
}