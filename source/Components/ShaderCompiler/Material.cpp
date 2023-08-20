#include "Material.h"


void Material::init() {
	shaderProgram = Shader (vertexPath.c_str(), fragmentPath.c_str());

	VAO1.Bind();

	/*VBO1 = VBO (entity->getComponent<SpriteComponent>().getVertices(), entity->getComponent<SpriteComponent>().getIndicesSize());
	EBO1 = EBO (entity->getComponent<SpriteComponent>().getIndices(), entity->getComponent<SpriteComponent>().getIndicesSize());
	vao = VAO1.ID;
	ebo = EBO1.ID;
	vbo = VBO1.ID;*/


	VAO1.LinkVBO (VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}



void Material::update() {
	shaderProgram.Activate();
	VAO1.Bind();
	vao = VAO1.ID;
}



void Material::draw() {

}


void Material::clean() {
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
}