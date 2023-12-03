#include "UIButton.h"

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
}


void UIButton::draw() {
    shader->use();
    glm::vec2 translationValue(5.0f, 0.0f); // Ajusta según tus necesidades
    shader->setVec2("inPosition", translationValue);

    glActiveTexture(GL_TEXTURE0);

    //DIFFUSE TEXTURE
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);


    // Enlazar VAO
    glBindVertexArray(VAO);

    // Dibujar el plano
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Desenlazar VAO
    glBindVertexArray(0);
}

void UIButton::CompilerShaders() {
    string newPathVERT = FileSystem::GetAsset(VertexPath);
    string newPathFRAG= FileSystem::GetAsset(FragmentPath);
    shader = new Shader(newPathVERT.c_str(), newPathFRAG.c_str());
    shader->use();
}

void UIButton::LoadTexture (string Path) {
    std::cout << "La nueva ruta de la textura es " << Path << std::endl;
    int width, height, nrChannels;
    string newPath = FileSystem::GetAsset("UI/button.png");
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

}