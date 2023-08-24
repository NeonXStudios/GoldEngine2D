#pragma once

#include <iostream>
#include <errno.h>
#include <fstream>

using namespace std;

class FileSystem
{
public:
	static string GetAsset (string path);
};