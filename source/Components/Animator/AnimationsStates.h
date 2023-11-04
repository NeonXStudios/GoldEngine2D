#pragma once
#include "../../source/EngineBehaviour/GoldEngineLib.h"
#include <iostream>
#include <vector>

using namespace std;

class AnimationsStates
{
	int currentFrame;

public:
	SpriteComponent* cp;
	string StateName;
	vector<string> FramesPath = vector<string>();
	vector<GLuint> Frames = vector<GLuint>();
	bool Rebuilding;

	void AddNewFrame(string path);
	void BuildTexture(string path);
	void UpdateState();
	void RebuildState();
};