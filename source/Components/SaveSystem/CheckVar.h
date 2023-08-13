#pragma once
#include <iostream>
#include "nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

class CheckVar
{
public:
	static bool Has (json js, string nameVar);
};