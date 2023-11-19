#pragma once
#include <iostream>
#include <filesystem>
#include <string.h>
#include "../../UI/DragAndDrop.h"
#include "../../UI/HUDS/Inspector.h"
#include "../UIDrawer.h"
#include <stb_image.h>
#include <fstream>

namespace fs = std::filesystem;
using namespace std;

class AssetsUI : public UIDrawer {

public:

    struct assetIcon {
        static GLuint start(string p, string gPath) {
            GLuint texture_id;
            unsigned char* image_data;
            int width, height, channels;
            string pat = "Editor/engine/ICONS/" + p;
            std::cout << "Icons Path: " << gPath << std::endl; 
            image_data = stbi_load(pat.c_str(), &width, &height, &channels, STBI_rgb_alpha);
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
            glGenerateMipmap(GL_TEXTURE_2D);

            return texture_id;
        }
    };


    bool isDragging = false;
    bool assetsMenuOpen = false;

    string pathG = "NULL";
    string assetPath = "NULL";
    std::string path_to_read = "/assets/";
    GLuint sceneTextureID;
    GLuint scriptTextureID;
    GLuint folderTextureID;
    GLuint shaderTextureID;
    GLuint textureTextureID;
    GLuint musicTextureID;
    GLuint whereTextureID;
    GLuint fbxTextureID;
    ImVec2 mousePos;

    void start() override {
        path_to_read = getRoute() + "/assets/";

        folderTextureID  = assetIcon::start("folderpath.png" , pathG);
        scriptTextureID  = assetIcon::start("script.png", pathG);
        sceneTextureID   = assetIcon::start("scene.png", pathG);
        shaderTextureID  = assetIcon::start("shader.png", pathG);
        textureTextureID = assetIcon::start("texture.png", pathG);
        musicTextureID = assetIcon::start("music.png", pathG);
        whereTextureID = assetIcon::start("where.png", pathG);
        fbxTextureID = assetIcon::start("FBX.png", pathG);
    }

    void resetRoute();
    string getRoute();

    void HandleDroppedAsset()
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_PATH"))
        {
            assetPath = static_cast<const char*>(payload->Data);
        }
    }

    void draw() override;

    void update() override {

    }

    void lateupdate() override {

    }

    void fixupdate() override {

    }


    std::string obtenerNombreArchivo(const std::string& ruta) {
        size_t ultimaBarra = ruta.find_last_of("/\\");
        if (ultimaBarra != std::string::npos) {
            return ruta.substr(ultimaBarra + 1);
        }
        return ruta;
    }

    std::string obtenerRutaSinNombreArchivo(const std::string& ruta) {
        size_t ultimaBarra = ruta.find_last_of("/\\");
        if (ultimaBarra != std::string::npos) {
            return ruta.substr(0, ultimaBarra + 1);
        }
        return ""; 
    }
};