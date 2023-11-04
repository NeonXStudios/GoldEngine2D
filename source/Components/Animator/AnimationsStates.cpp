#include "AnimationsStates.h"


void AnimationsStates::UpdateState() {
    if (!Rebuilding && Frames.size() > 0) {
        currentFrame++;

        if (currentFrame >= Frames.size() - 1) {
            currentFrame = 0;
        }

        cp->texture = Frames[currentFrame];
    }
}

void AnimationsStates::AddNewFrame(string path) {
    FramesPath.push_back (path);
    BuildTexture (path);
}

void AnimationsStates::BuildTexture (string path) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configuraciones de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int width, height, nrChannels;
    string newPath = FileSystem::GetAsset(path);
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

    Frames.push_back(texture);
}

void AnimationsStates::RebuildState() {
    Rebuilding = true;
    Frames.clear();

    for (string framePath : FramesPath) {
        BuildTexture (framePath);
    }

    Rebuilding = false;
    std::cout << "States Rebuild Succefully" << std::endl;
}

void AnimationsStates::DeleteFrame (int index)
{
    if (index >= 0 && index < FramesPath.size()) {
        FramesPath.erase(FramesPath.begin() + index);

        std::cout << "Frame Path eliminado" << std::endl;
    }

    if (index >= 0 && index < Frames.size()) {
        Frames.erase(Frames.begin() + index);

        std::cout << "Frame eliminado" << std::endl;
    }
}