#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include <iostream>
#include <vector>
#include "../ShaderCompiler/shaderClass.h"
#include "../ShaderCompiler/VAO.h"
#include "../ShaderCompiler/VBO.h"
#include "../ShaderCompiler/EBO.h"
#include "../Camera/Camera2D.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;
	// Store VAO in public so it can be used in the Draw function
	VAO VAO;

	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);

	// Draws the mesh
	void Draw(Shader& shader, Camera& camera);
};
#endif