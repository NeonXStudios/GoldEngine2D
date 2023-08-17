#pragma once
#include <iostream>
#include <imgui/imgui.h>
#include "../../source/EngineBehaviour/GoldEngineLib.h"
#include <filesystem>
#include <string>
#include <cstdlib>


namespace fs = std::filesystem;

using namespace std;

class GoldHub : public EngineBehaviour {
public:
    string pathName = "New Game";
    string namePR = "Project Name";
    char* userProfilePath = nullptr;
    size_t requiredSize;
    std::string documentsPath;
    string proyectsPath;
    std::filesystem::path AppPath;
    std::filesystem::path currentPath;

    void start() override {
        _dupenv_s(&userProfilePath, &requiredSize, "USERPROFILE");

        if (userProfilePath != nullptr)
        {
            documentsPath = std::string(userProfilePath) + "\\Documents";
            std::cout << "Ruta de la carpeta de documentos: " << documentsPath << std::endl;

            // Libera la memoria asignada por _dupenv_s
            free(userProfilePath);
        }
        else
        {
            std::cout << "No se pudo obtener la ruta de la carpeta de documentos." << std::endl;
        }

        std::string ruta = documentsPath + "/GoldEngine/Projects/"; // Ruta de la carpeta que deseas crear

        if (!fs::exists(ruta)) {
            if (fs::create_directories(ruta)) {
                std::cout << "Carpeta creada exitosamente." << std::endl;
            }
            else {
                std::cerr << "Error al crear la carpeta." << std::endl;
            }
        }
        else {
            std::cout << "La carpeta ya existe." << std::endl;
        }


        proyectsPath = documentsPath + "/GoldEngine/Projects/";

        currentPath = std::filesystem::current_path();
        AppPath = currentPath;
        std::cout << "Ruta del programa: " << currentPath << std::endl;
    }

    void draw() override {


    }

    void update() override {
       
    }

    void lateupdate() override {

    }

    void fixupdate() override {

    }

    void drawUI() override {
        ImGui::DockSpaceOverViewport();
        ImGui::Begin ("GOLD ENGINE");
        ImGui::Text ("Projects");
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        
        {
            std::string documentsPath = documentsPath; // Ruta de tus documentos
            std::string ruta = proyectsPath;

            ImVec2 windowSize = ImGui::GetContentRegionAvail();

            if (fs::exists(ruta)) {

                for (const auto& entrada : fs::directory_iterator(ruta)) {
                    if (fs::is_directory(entrada.status())) {
                        if (ImGui::Button(entrada.path().filename().string().c_str(), ImVec2(windowSize.x - 20, 70))) {
                            const char* programa = "Editor/GoldEditor.exe";

                            string argumento = entrada.path().string();

                            std::string directorio_actual = std::filesystem::current_path().string();

                            std::string ruta_completa = directorio_actual + "\\" + programa;

                            std::string comando = "\"" + ruta_completa + "\" " + argumento;

                            int resultado = std::system(comando.c_str());

                            if (resultado == 0) {
                                // El programa se ejecut� exitosamente
                            }
                            else {
                                // Hubo un error al abrir el programa
                            }
                        }
                    }
                }
            }
            else {
                std::cerr << "La ruta no existe." << std::endl;
            }
        }

        ImGui::End();

        ImGui::Begin ("New Project");
        const char* path = proyectsPath.c_str();
        ImGui::Text (path);
        ImGui::NewLine();
        char getName[128];
        strcpy_s(getName, pathName.c_str());
        ImGui::InputText(_labelPrefix(namePR.c_str()).c_str(), getName, 9999);
        pathName = (string)getName;
        if (ImGui::Button("Create")) {
            for (size_t i = 0; i < pathName.length(); ++i) {
                if (pathName[i] == ' ') {
                    pathName[i] = '_';
                }
            }
            std::string ruta = documentsPath + "/GoldEngine/Projects/" + pathName; // Ruta de la carpeta que deseas crear

            if (!fs::exists(ruta)) {
                if (fs::create_directories(ruta)) {
                    std::cout << "Carpeta creada exitosamente." << std::endl;
                }
                else {
                    std::cerr << "Error al crear la carpeta." << std::endl;
                }
            }
            else {
                std::cout << "La carpeta ya existe." << std::endl;
            }
        }
        ImGui::End();

        //std::cout << "CARPETA DOCUMENTS: " << proyectsPath << std::endl;
    }

    void release() override {

    }


    std::string _labelPrefix(const char* const label)
    {
        float width = ImGui::CalcItemWidth();

        float x = ImGui::GetCursorPosX();
        ImGui::Text(label);
        ImGui::SameLine();
        ImGui::SetCursorPosX(x + width * 0.5f + ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::SetNextItemWidth(-1);

        std::string labelID = "##";
        labelID += label;

        return labelID;
    }
};