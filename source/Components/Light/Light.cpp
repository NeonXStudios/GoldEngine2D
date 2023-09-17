#include "Light.h"



void Light::init() {
	shader = new Shader (Directionvert.c_str(), Directionfrag.c_str());
	LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	shader->use();
	shader->setVec4("lightColor", LightColor);

	//glGenFramebuffers(1, &shadowMapFBO);

	//glGenTextures(1, &shadowMap);
	//glBindTexture(GL_TEXTURE_2D, shadowMap);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	//// Prevents darkness outside the frustrum
	//float clampColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

	//glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	//// Needed since we don't touch the color buffer
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//// Matrices needed for the light's perspective
	//orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
	//lightView = glm::lookAt(20.0f * entity->transform->Position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//lightProjection = orthgonalProjection * lightView;

	//shadowMapshader = new Shader (ShadowMapVert.c_str(), ShadowMapFrag.c_str());
	//shadowMapshader->use();
	//shadowMapshader->setMat4 ("lightProjection", lightProjection);
}



void Light::update() {

}

void Light::preRenderShadow() {
	glEnable(GL_DEPTH_TEST);

	// Preparations for the Shadow Map
	glViewport(0, 0, shadowMapWidth, shadowMapHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	entity->getComponent<SpriteComponent>().ourmodel->Draw(*shadowMapshader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, AppSettings::RenderWidth, AppSettings::RenderHeight);
}



void Light::draw() {
	shader->use();

	shader->setMat4 ("view", SceneManager::GetSceneManager()->OpenScene->worldCamera->GetView());
	shader->setMat4 ("projection", SceneManager::GetSceneManager()->OpenScene->worldCamera->GetProjectionMatrix());
	shader->setMat4 ("model", entity->transform->GetMatrix());
	shader->setVec4 ("lightColor", LightColor);

	//entity->getComponent<SpriteComponent>().ourShader->setVec3 ("lightPos", entity->transform->Position);

	//Entity* objTest = SceneManager::GetSceneManager()->OpenScene->objectsInScene[SceneManager::GetSceneManager()->OpenScene->objectsInScene.size() - 1];
	//objTest->getComponent <SpriteComponent>().ourShader->setVec4("lightColor", LightColor);
	//objTest->getComponent <SpriteComponent>().ourShader->setVec3("lightPos", entity->transform->Position);
	//objTest->getComponent <SpriteComponent>().ourShader->setVec3("camPos", SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition);
	//glUniformMatrix4fv(glGetUniformLocation(objTest->getComponent <SpriteComponent>().ourShader->ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));

	//std::cout << "Try draw shadows" << std::endl;
}



void Light::PreRender() {

}

void Light::PostRender() {
	//glActiveTexture(GL_TEXTURE0 + 2);
	//glBindTexture(GL_TEXTURE_2D, shadowMap);
	//glUniform1i(glGetUniformLocation(shadowMapshader->ID, "shadowMap"), 2);

	//Entity* objTest = SceneManager::GetSceneManager()->OpenScene->objectsInScene[SceneManager::GetSceneManager()->OpenScene->objectsInScene.size() - 1];
	//objTest->getComponent <SpriteComponent>().ourmodel->Draw (*objTest->getComponent <SpriteComponent>().ourShader);
}
