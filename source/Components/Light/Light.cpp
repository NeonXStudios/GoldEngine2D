#include "Light.h"



void Light::init() {
	shader = new Shader (vert.c_str(), frag.c_str());
	LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	shader->use();
	shader->setVec4("lightColor", LightColor);
}



void Light::update() {

}



void Light::draw() {
	shader->use();
	shader->setMat4 ("model", entity->transform->GetMatrix());
	shader->setMat4 ("camMatrix", SceneManager::GetSceneManager()->OpenScene->worldCamera->GetCameraMatrix());
	shader->setVec4 ("lightColor", LightColor);

	Entity* objTest = SceneManager::GetSceneManager()->OpenScene->objectsInScene[SceneManager::GetSceneManager()->OpenScene->objectsInScene.size() - 1];
	objTest->getComponent <SpriteComponent>().ourShader->setVec4("lightColor", LightColor);
	objTest->getComponent <SpriteComponent>().ourShader->setVec3("lightPos", entity->transform->Position);
	objTest->getComponent <SpriteComponent>().ourShader->setVec3("camPos", SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition);
}



void Light::PreRender() {

}

void Light::PostRender() {

}
