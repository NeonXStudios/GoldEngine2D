#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "../../Graphics/StartEngineGraphics.h"
#include <iostream>

class UIImplement
{
public:
	void start();
	void draw();
	void DrawCanvas();
	void DrawData();

	~UIImplement();
};