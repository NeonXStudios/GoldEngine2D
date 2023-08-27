#pragma once
#include <GoldEngineLib.h>

class GDGizmos
{
public:
	static void DrawCube (){
        glBegin(GL_QUADS);

        // Front face
        glColor3f(1.0f, 0.0f, 0.0f);  // Red color
        glVertex3f(-0.5f, -0.5f, 0.5f);  // Bottom-left vertex
        glVertex3f(0.5f, -0.5f, 0.5f);   // Bottom-right vertex
        glVertex3f(0.5f, 0.5f, 0.5f);    // Top-right vertex
        glVertex3f(-0.5f, 0.5f, 0.5f);   // Top-left vertex

        // Back face
        glColor3f(0.0f, 1.0f, 0.0f);  // Green color
        glVertex3f(-0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);
        glVertex3f(-0.5f, 0.5f, -0.5f);

        glEnd();



	}
};