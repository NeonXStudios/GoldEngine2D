#include "SpriteComponent.h"
#define STB_IMAGE_IMPLEMENTATIONTEXTURE
#include <stb_image.h>
#include "nlohmann/json.hpp"
#include "../SaveSystem/CheckVar.h"
#include "../FileSystem/FileSystem.h"
#include "../Systems/SystemsEvents.h"

using namespace nlohmann;

float vertices2[] = {
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f
};

unsigned int indices2[] = {
    0, 1, 2,
    2, 3, 0,
    4, 5, 6,
    6, 7, 4,
    0, 4, 5,
    5, 1, 0,
    1, 5, 6,
    6, 2, 1,
    2, 6, 7,
    7, 3, 2,
    3, 7, 4,
    4, 0, 3
};

void SpriteComponent::start()  {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configuraciones de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    compileShaders();
    LoadTexture();
}

void SpriteComponent::LoadTexture () {
    //glDeleteTextures(1, &texture);

    std::cout << "La nueva ruta de la textura es " << TexturePath << std::endl;
    int width, height, nrChannels;
    string newPath = FileSystem::GetAsset (TexturePath);
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

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);


    std::cout << "La nueva ruta de la textura es " << TextureSpecularPath << std::endl;
    int widthSpecular , heightSpecular, nrChannelsSpecular;
    string newPathSpecular = FileSystem::GetAsset(TextureSpecularPath);
    std::cout << "NUEVA RUTA:" << newPath << std::endl;

    unsigned char* dataSpecular = stbi_load(newPathSpecular.c_str(), &widthSpecular, &heightSpecular, &nrChannelsSpecular, 0);
    if (data) {
        glBindTexture(GL_TEXTURE_2D, textureSpecular);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, widthSpecular, heightSpecular, 1, GL_RED, GL_UNSIGNED_BYTE, dataSpecular);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(dataSpecular);
}

void SpriteComponent::onupdate() {
    if (entity->hasComponent<MaterialComponent>()) {
        //glUseProgram(ourShader->ID);
//        ourShader->use();
        glActiveTexture(GL_TEXTURE0);

        //DIFFUSE TEXTURE
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(entity->getComponent<MaterialComponent>().ourShader->ID, "texture_diffuse1"), 0);

        //SPECULAR MAP
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(entity->getComponent<MaterialComponent>().ourShader->ID, "texture_specular1"), 0);

        entity->getComponent<MaterialComponent>().ourShader->use();
        entity->getComponent<MaterialComponent>().ourShader->setMat4("view", SceneManager::GetSceneManager()->OpenScene->worldCamera->GetView());
        entity->getComponent<MaterialComponent>().ourShader->setVec3("camPos", SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition);
        entity->getComponent<MaterialComponent>().ourShader->setMat4("projection", SceneManager::GetSceneManager()->OpenScene->worldCamera->GetProjectionMatrix());
        entity->getComponent<MaterialComponent>().ourShader->setMat4("model", entity->transform->GetMatrix());  // Aplicar la matriz de modelo
        ourmodel->Draw(*entity->getComponent<MaterialComponent>().ourShader);
    }
}

void SpriteComponent::draw() {

}

void SpriteComponent::PreRender() {

}

void SpriteComponent::PostRender() {

}


void SpriteComponent::clean() {
    glDeleteTextures(1, &texture);
}



std::string SpriteComponent::serialize() {
    json componentData;
    componentData["scalex"] = entity->transform->Scale.x; 
    componentData["scaley"] = entity->transform->Scale.y;
    componentData["scalez"] = entity->transform->Scale.z;

    componentData["texturepath"] = TexturePath;

    return componentData.dump();
}

void SpriteComponent::deserialize (std::string g, std::string path) {
    json componentData = json::parse(g);


    if (CheckVar::Has(componentData, "scalex"))
        entity->transform->Scale.x = componentData["scalex"];

    if (CheckVar::Has(componentData, "scaley"))
        entity->transform->Scale.y = componentData["scaley"];

    if (CheckVar::Has(componentData, "scalez"))
        entity->transform->Scale.z = componentData["scalez"];


    if (CheckVar::Has(componentData, "texturepath")) {
        string newPath = (string)componentData["texturepath"];
        TexturePath = newPath;
    }


    LoadTexture();
}

glm::mat4 SpriteComponent::GetMatrix() {
    glm::mat4 matrix;

    matrix = glm::translate(glm::mat4(1.0f), glm::vec3 (entity->transform->Position.x, entity->transform->Position.y, 0));
    matrix *= glm::mat4_cast(glm::quat(1, 0, 0, 0));
    matrix = glm::scale(matrix, entity->transform->Scale);

    return matrix;
}



float* SpriteComponent::getVertices() {
    return vertices2;
}

std::size_t SpriteComponent::getIndicesSize() {
    return sizeof(indices2);
}



GLuint* SpriteComponent::getIndices() {
    return indices2;
}

void SpriteComponent::compileShaders() {
    ourmodel = new GLD::Model(FileSystem::GetAsset("/models/Plane.fbx"));
}


glm::vec3 SpriteComponent::Min()

{
    return m_Min;
}

glm::vec3 SpriteComponent::Max()
{
    return m_Max;
}
