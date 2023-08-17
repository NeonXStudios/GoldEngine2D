#pragma once
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

class GameCompiler
{
public:
	static void compileWindow();
	static void copyDirectory(const fs::path& source, const fs::path& destination);
	static void ReplaceDir (string filePath);
};