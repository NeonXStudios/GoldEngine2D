#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct Mask {
	int Index = 0;
	string name = "Default";
};

class LayerMaskSystem
{
private:
	static LayerMaskSystem* instance;

public:
	vector <Mask*> GameMask = vector<Mask*>();
	static void StartMaskSystem();
	static void ClearSystem();
	static LayerMaskSystem* GetSystem();
	
	void AddLayer (string nameLayer);
	void GetLayers();
};