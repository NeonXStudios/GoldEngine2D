#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Mask {
	int Index;
	string name;
};

class LayerMaskSystem
{
private:
	vector <Mask*> GameMask = vector<Mask*>();
	static LayerMaskSystem* instance;

public:

	static void StartMaskSystem();
	static void ClearSystem();
	static LayerMaskSystem* GetSystem();
};