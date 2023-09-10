#include "Skybox.h"
#define STBLK
#include "stb_image.h"


void Skybox::init() {
	string newPathVertex = FileSystem::GetAsset(VertexPath);
	string newPathFrag = FileSystem::GetAsset(FragmentPath);

	ourShader = new Shader(newPathVertex.c_str(), newPathFrag.c_str());
	ourmodel = new GLD::Model(modelPath);
	ourShader->setFloat ("texture_diffuse1", 0);
	ourShader->use();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Configuraciones de la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glEnable(GL_BLEND);
 //   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	std::cout << "La nueva ruta de la textura es " << TexturePath << std::endl;
	int width, height, nrChannels;
	string newPath = FileSystem::GetAsset(TexturePath);
	std::cout << "NUEVA RUTA:" << newPath << std::endl;

	unsigned char* data = stbi_load(newPath.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format; 
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glBindTexture		(GL_TEXTURE_2D, texture															);
		glTexImage2D		(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data		);
		glGenerateMipmap	(GL_TEXTURE_2D																	);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	


	//SKYBOX BUFFER START
	glGenTextures(1, &skyboxTexture);
	glBindTexture(GL_TEXTURE_2D, skyboxTexture);
	// Configura los parámetros de textura aquí (min/mag filter, wrap mode, etc.)

	// Configurar la textura de profundidad
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, AppSettings::RenderWidth, AppSettings::RenderHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Configurar el framebuffer del skybox
	glGenFramebuffers(1, &skyboxFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, skyboxFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, skyboxTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	// Verificar el estado del framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Error: Framebuffer del skybox no está completo" << std::endl;
	}

	// Restaurar el framebuffer predeterminado
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Skybox::draw() {

}

void Skybox::update() {
	glUseProgram(ourShader->ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(ourShader->ID, "texture_diffuse1"), 0);

	Rotation.z = -90;

	Matrix = glm::mat4(1.0f);
	vec3 cameraPos = SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition;
	// Aplicar traslación
	Matrix = glm::translate(Matrix, glm::vec3(Position.x, Position.y, Position.z));
	glm::quat rotationZ = glm::angleAxis(glm::radians(Rotation.x), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::quat rotationY = glm::angleAxis(glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat rotationX = glm::angleAxis(glm::radians(Rotation.z), glm::vec3(1.0f, 0.0f, 0.0f));

	rotation = rotationZ * rotationY * rotationX;

	//glm::mat4 rotationMatrix = glm::mat4_cast(rotation);


	Matrix *= glm::mat4_cast(rotation);
	Matrix = glm::scale(Matrix, glm::vec3(Scale.x, Scale.y, Scale.z));

	ourShader->use();
	ourShader->setMat4("view", SceneManager::GetSceneManager()->OpenScene->worldCamera->GetView());
	ourShader->setMat4("projection", SceneManager::GetSceneManager()->OpenScene->worldCamera->GetProjectionMatrix());
	ourShader->setMat4("model", GetMatrix());  // Aplicar la matriz de modelo
	ourmodel->Draw(*ourShader);
	Position = cameraPos;
}

void Skybox::PreRender() {

}


void Skybox::PostRender() {

}


void Skybox::clean() {

}

glm::mat4 Skybox::GetMatrix() {
	return Matrix;
}