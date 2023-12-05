#include "UIButton.h"
#include "../../SceneManager/SceneManager.h"

float vertices23[] = {
    // Posiciones           // Coordenadas de textura
   -0.5f,  0.5f,  0.0f, 1.0f,   // Arriba izquierda
   -0.5f, -0.5f,  0.0f, 0.0f,   // Abajo izquierda
    0.5f, -0.5f,  1.0f, 0.0f,   // Abajo derecha

   -0.5f,  0.5f,  0.0f, 1.0f,   // Arriba izquierda
    0.5f, -0.5f,  1.0f, 0.0f,   // Abajo derecha
    0.5f,  0.5f,  1.0f, 1.0f    // Arriba derecha
};


void UIButton::start() {

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, 0);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configuraciones de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    CompilerShaders();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Enlazar el VAO
    glBindVertexArray(VAO);

    // Enlazar y configurar el VBO para almacenar los vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices23), vertices23, GL_STATIC_DRAW);

    // Configurar el atributo de posición
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Configurar el atributo de coordenadas de textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Desenlazar VAO y VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LoadTexture();
    currentAnchor = AnchorUI::Bottom;
}

void UIButton::draw() {
    Matrix = glm::mat4(1.0f);

    if (currentAnchor == AnchorUI::None) {
        Matrix = glm::translate(Matrix, glm::vec3(Position.x, Position.y, Position.z) + Offset);
    }
    else if(currentAnchor == AnchorUI::Left)
    {
        float ScreenX = -AppSettings::RenderWidth + (widthTXT / 2);
        Matrix = glm::translate(Matrix, glm::vec3(ScreenX, Position.y, Position.z) + Offset);
    }
    else if (currentAnchor == AnchorUI::Right)
    {
        float ScreenX = AppSettings::RenderWidth - (widthTXT / 2);
        Matrix = glm::translate(Matrix, glm::vec3(ScreenX, Position.y, Position.z) + Offset);
    }
    else if (currentAnchor == AnchorUI::Top)
    {
        float ScreenY = AppSettings::RenderHeight - (heightTXT / 2);
        Matrix = glm::translate(Matrix, glm::vec3(Position.x, ScreenY, Position.z) + Offset);
    }
    else if (currentAnchor == AnchorUI::Bottom)
    {
        float ScreenY = -AppSettings::RenderHeight + (heightTXT / 2);
        Matrix = glm::translate(Matrix, glm::vec3(Position.x, ScreenY, Position.z) + Offset);
    }
    
    glm::quat rotationZ = glm::angleAxis(glm::radians(Rotation.x), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::quat rotationY = glm::angleAxis(glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat rotationX = glm::angleAxis(glm::radians(Rotation.z), glm::vec3(1.0f, 0.0f, 0.0f));

    rotation = rotationZ * rotationY * rotationX;

    Matrix *= glm::mat4_cast(rotation);
    Matrix = glm::scale(Matrix, Scale);

    ourShader->use();
    glActiveTexture(GL_TEXTURE0);

    //DIFFUSE TEXTURE
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(ourShader->ID, "texture_diffuse1"), 0);

    //SPECULAR MAP
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(ourShader->ID, "texture_specular1"), 0);

    float aspectRatio = 1920.0f / 1080.0f; // Calcula la relación de aspecto 1920x1080

    // Calcula un FOV basado en la relación de aspecto para una apariencia apropiada
    float fov = 60.0f; // Por ejemplo, un FOV de 60 grados

    // Calcula la matriz de proyección con el FOV y la relación de aspecto
    glm::mat4 projection = glm::ortho(float(-AppSettings::RenderWidth), float(AppSettings::RenderWidth), float(-AppSettings::RenderHeight), float(AppSettings::RenderHeight), -1000.0f, 1000.0f);


    //ourShader->setVec3("camPos", SceneManager::GetSceneManager()->OpenScene->worldCamera->cameraPosition);
    //ourShader->setMat4("view", SceneManager::GetSceneManager()->OpenScene->worldCamera->GetView());
    ourShader->setMat4("projection", projection);
    ourShader->setMat4("model", Matrix);  // Aplicar la matriz de modelo
    ourmodel->Draw(*ourShader);
}

void UIButton::CompilerShaders() {
    ourmodel = new GLD::Model(FileSystem::GetAsset("/models/Plane.fbx"));
    string newPathVERT = FileSystem::GetAsset(VertexPath);
    string newPathFRAG= FileSystem::GetAsset(FragmentPath);
    ourShader = new Shader(newPathVERT.c_str(), newPathFRAG.c_str());
    ourShader->use();
}

void UIButton::onClick() {

}

void UIButton::LoadTexture (string Path) {
    std::cout << "=*=*=*=*=*=*=*=*=*= TEXTURE UI PATH" << Path << std::endl;
    int width, height, nrChannels;
    string newPath = FileSystem::GetAsset(Path);
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

    widthTXT = width;
    heightTXT = height;

    stbi_image_free(data);
}