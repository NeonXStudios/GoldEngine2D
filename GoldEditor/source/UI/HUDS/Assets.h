#pragma once
#include <iostream>
#include <filesystem>
#include <string.h>

#include "../UIDrawer.h"
#include <stb_image.h>

namespace fs = std::filesystem;
using namespace std;

class AssetsUI : public UIDrawer {

public:
    struct assetIcon {
        static GLuint start(string p) {
            GLuint texture_id;
            unsigned char* image_data;
            int width, height, channels;
            string pat = "game/engine/ICONS/" + p;
            image_data = stbi_load(pat.c_str(), &width, &height, &channels, STBI_rgb_alpha);
            glGenTextures(1, &texture_id);
            glBindTexture(GL_TEXTURE_2D, texture_id);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
            glGenerateMipmap(GL_TEXTURE_2D);

            return texture_id;
        }
    };

    string assetPath;
    bool isDragging = false;
    std::string path_to_read = "game/assets/";

    GLuint sceneTextureID;
    GLuint scriptTextureID;
    GLuint folderTextureID;
    GLuint shaderTextureID;
    GLuint textureTextureID;
    GLuint musicTextureID;

    void start() override {
        folderTextureID = assetIcon::start("folderpath.png");
        scriptTextureID = assetIcon::start("script.png");
        sceneTextureID = assetIcon::start("scene.png");
        shaderTextureID = assetIcon::start("shader.png");
        textureTextureID = assetIcon::start("texture.png");
        musicTextureID = assetIcon::start("music.png");
    }

    void HandleDroppedAsset()
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSET_PATH"))
        {
            assetPath = static_cast<const char*>(payload->Data);
        }
    }

    void draw() override {
        string pathallName = "Assets";

        ImGui::Begin (pathallName.c_str());

        if (path_to_read != "game/assets/") {
            if (ImGui::Button ("<")) {
                path_to_read = "game/assets/";
            }
        }

        ImGuiDragDropFlags src_flags = 0;
        src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
        src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging


        ImGui::BeginChild(path_to_read.c_str());
            ImVec2 getWidthWindow = ImGui::GetContentRegionAvail();

            try {
                for (const auto& entry : fs::directory_iterator(path_to_read)) {
                    std::string namePath = entry.path().filename().string();
                    ImGui::PushID(namePath.c_str());

                    ImVec2 imageSize(50, 50); // Tamaño de la imagen
                    ImVec2 textPadding(0, 5); // Espaciado entre la imagen y el texto

                    // Guardar la posición actual para dibujar el texto superpuesto
                    ImVec2 textPos = ImGui::GetCursorScreenPos();
                    textPos.y += imageSize.y + textPadding.y;

                    ImVec2 getPosIMG = ImGui::GetCursorPos();

                    // Dibujar la imagen
                    

                    if (fs::is_directory(entry)) {
                        if (ImGui::ImageButton((void*)(intptr_t)folderTextureID, imageSize)) {
                            path_to_read = entry.path().string();
                            std::cout << "Entering path: " << path_to_read << std::endl;
                        }
                    }
                    
                    if (fs::is_regular_file(entry)) {
                        std::string extension = entry.path().extension().string();

                            if (extension == ".scene") {
                                if (ImGui::ImageButton((void*)(intptr_t)sceneTextureID, imageSize)) {
                                    //path_to_read = entry.path().string();
                                }
                            }

                            if (ImGui::BeginDragDropSource(src_flags))
                            {
                                const char* filePathN;
                                string t = "Moving " + namePath;
                                ImGui::Text(t.c_str());

                                std::string pathToSend = entry.path().string();
                                ImGui::SetDragDropPayload("SCENE_PATH", pathToSend.c_str(), pathToSend.size() + 1); // +1 para incluir el carácter nulo
                                ImGui::EndDragDropSource();
                            }



                            if (extension == ".glsl") {
                                if (ImGui::ImageButton((void*)(intptr_t)shaderTextureID, imageSize)) {
                                    //path_to_read = entry.path().string();
                                }
                            }

                            if (ImGui::BeginDragDropSource(src_flags))
                            {
                                const char* filePathN;
                                string t = "Moving " + namePath;
                                ImGui::Text(t.c_str());

                                std::string pathToSend = entry.path().string();
                                ImGui::SetDragDropPayload("SHADER_PATH", pathToSend.c_str(), pathToSend.size() + 1); // +1 para incluir el carácter nulo
                                ImGui::EndDragDropSource();
                            }


                            if (extension == ".mp3") {
                                if (ImGui::ImageButton((void*)(intptr_t)musicTextureID, imageSize)) {
                                    //path_to_read = entry.path().string();
                                }
                            }

                            if (ImGui::BeginDragDropSource(src_flags))
                            {
                                const char* filePathN;
                                string t = "Moving " + namePath;
                                ImGui::Text(t.c_str());

                                std::string pathToSend = entry.path().string();
                                ImGui::SetDragDropPayload("MUSICMP_PATH", pathToSend.c_str(), pathToSend.size() + 1); // +1 para incluir el carácter nulo
                                ImGui::EndDragDropSource();
                            }




                            if (extension == ".png" || extension == ".gif") {
                                if (ImGui::ImageButton((void*)(intptr_t)textureTextureID, imageSize)) {
                                    //path_to_read = entry.path().string();
                                }
                            }

                            if (ImGui::BeginDragDropSource(src_flags))
                            {
                                const char* filePathN;
                                string t = "Moving " + namePath;
                                ImGui::Text(t.c_str());

                                std::string pathToSend = entry.path().string();
                                ImGui::SetDragDropPayload("TXTTURE_PATH", pathToSend.c_str(), pathToSend.size() + 1); // +1 para incluir el carácter nulo
                                ImGui::EndDragDropSource();
                            }





                            if (extension == ".sr") {
                                if (ImGui::ImageButton((void*)(intptr_t)scriptTextureID, imageSize)) {
                                    string path = entry.path().string();
                                    const char* fileName = path.c_str();

                                    const char* command = "code";
                                    const char* arguments = fileName;

                                    char fullCommand[100];
                                    snprintf(fullCommand, sizeof(fullCommand), "%s %s", command, arguments);

                                    int result = system(fullCommand);

                                    if (result == 0) {
                                        printf("Archivo abierto exitosamente con VSCode.\n");
                                    }
                                    else {
                                        printf("Error al abrir el archivo con VSCode.\n");
                                    }
                                }
                            }
                        }



                    //src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip; // Hide the tooltip

                    if (ImGui::BeginDragDropSource(src_flags))
                    {
                        const char* filePathN;
                        string t = "Moving " + namePath;
                        ImGui::Text(t.c_str());

                        std::string pathToSend = entry.path().string();
                        ImGui::SetDragDropPayload("SRSCRIPT_PATH", pathToSend.c_str(), pathToSend.size() + 1); // +1 para incluir el carácter nulo
                        ImGui::EndDragDropSource();
                    }




                    

                        ImVec2 posicionImagen = getPosIMG;
                    if (entry.path().extension() != ".f") {

                        ImDrawList* drawList = ImGui::GetWindowDrawList();
                        ImFont* font = ImGui::GetFont(); // Obtiene la fuente actual de ImGui

                        std::string text = namePath; // Tu cadena de texto original
                        //ImVec2 textPos = ImVec2(0.0f, 0.0f); // Posición del texto
                        ImU32 textColor = IM_COL32_WHITE; // Color del texto

                        int maxLetters = 7; // Máximo de letras que deseas mostrar

                        if (text.size() > maxLetters) {
                            text = text.substr(0, maxLetters); // Obtén solo las primeras 9 letras
                        }

                        drawList->AddText(font, font->FontSize, ImVec2(0.0f, 0.0f), textColor, text.c_str());

                        drawList->AddText(font, font->FontSize, textPos, textColor, text.c_str());
                    }
                    ImGui::PopID();


                    float espacioHorizontal = 5.0f;
                    float anchoImagen = 50.0f;
                    float espacioTotalImagen = anchoImagen + espacioHorizontal;

                    if (posicionImagen.x + espacioTotalImagen < ImGui::GetContentRegionAvail().x - 50) {
                        ImGui::SameLine();
                    }
                    else {
                        ImGui::NewLine();
                    }

                    
                }
            }
            catch (const fs::filesystem_error& ex) {
                std::cerr << "Error al acceder a la ruta: " << ex.what() << std::endl;
            }





            
            ImGui::EndChild();
        
        ImGui::End();
    }


    void update() override {

    }

    void lateupdate() override {

    }

    void fixupdate() override {

    }
};