#include "GameCompiler.h"
#include "GoldEditor.h"
#include <iostream>

#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <algorithm>

using namespace nlohmann;
using namespace std;


void GameCompiler::compileWindow()
{
    {
        std::string folderName = GoldEditor::editor->ProjectPath + "/GameBuild/";

        if (fs::create_directory(folderName)) {
            std::cout << "Carpeta creada exitosamente." << std::endl;
        }
        else {
            std::cerr << "Error al crear la carpeta." << std::endl;
        }
    }

    {
        std::string folderName = GoldEditor::editor->ProjectPath + "/GameBuild/game/";

        if (fs::create_directory(folderName)) {
            std::cout << "Carpeta creada exitosamente." << std::endl;
        }
        else {
            std::cerr << "Error al crear la carpeta." << std::endl;
        }
    }


    std::string sourceFilePath = "Editor/DATA/WINCOMPILER/GoldGame.exe";
    std::string destinationFilePath = GoldEditor::editor->ProjectPath + "/GameBuild/GoldGame.exe";

    try {
        fs::copy(sourceFilePath, destinationFilePath, fs::copy_options::overwrite_existing);
        std::cout << "Archivo copiado exitosamente." << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error al copiar el archivo: " << e.what() << std::endl;
    }


    std::string folderPath = GoldEditor::editor->ProjectPath + "/GameBuild/";

    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            std::cout << entry.path() << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error al acceder a la carpeta: " << e.what() << std::endl;
    }

    std::string sourceFolderPath = "Editor/BIN/DLL/";
    std::string destinationFolderPath = GoldEditor::editor->ProjectPath + "/GameBuild/";

    try {
        for (const auto& entry : fs::directory_iterator(sourceFolderPath)) {
            fs::copy(entry.path(), destinationFolderPath + entry.path().filename().string(), fs::copy_options::overwrite_existing);
            std::cout << "Archivo copiado: " << entry.path() << std::endl;
        }
        std::cout << "Todos los archivos han sido copiados." << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error al copiar los archivos: " << e.what() << std::endl;
    }


    json gameData;
    gameData["gameRun"] = true;

    std::ofstream file (destinationFolderPath + "/gamedata.json");

    if (file.is_open()) {
        file << gameData.dump(4); // Indentación de 4 espacios
        file.close();
        std::cout << "Archivo JSON creado exitosamente." << std::endl;
    }
    else {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }
    file.close();



    std::string projectPath = GoldEditor::editor->ProjectPath;

    fs::path sourceFolder = projectPath + "/assets";
    fs::path destinationFolder = GoldEditor::editor->ProjectPath + "/GameBuild/game";

    copyDirectory(sourceFolder, destinationFolder);
    std::cout << "Game compiled... (PLATAFORM WINDOW)" << std::endl;
}



void GameCompiler::copyDirectory(const fs::path& source, const fs::path& destination) {
    try {
        fs::create_directories(destination);
        for (const auto& entry : fs::directory_iterator(source)) {
            const fs::path entryPath = entry.path();
            const fs::path newDestination = destination / entryPath.filename();
            if (fs::is_directory(entryPath)) {
                copyDirectory(entryPath, newDestination);
            }
            else {
                if (entryPath.extension() == ".scene") {
                    fs::create_directories(destination / "scenes");
                    string filePaht = destination.string() + string("/scenes/") + entryPath.filename().string();
                    fs::copy(entryPath, destination / "scenes" / entryPath.filename(), fs::copy_options::overwrite_existing);
                    ReplaceDir (filePaht);
                }
                else {
                    fs::copy(entryPath, newDestination, fs::copy_options::overwrite_existing);
                }
            }
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}


void GameCompiler::ReplaceDir(string filePath) {

    std::string path = GoldEditor::editor->ProjectPath;

    std::string::size_type pos = 0;
    while ((pos = path.find("\\", pos)) != std::string::npos) {
        path.replace(pos, 1, "\\\\");
        pos += 2;
    }

    std::cout << "Ruta con barras invertidas dobles: " << path << std::endl;

    {
        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            std::cerr << "No se pudo abrir el archivo." << std::endl;
        }

        json jsonData;
        inputFile >> jsonData;
        std::cout << "JSON READ" << jsonData.dump (4) << std::endl;
        inputFile.close();
    }

    std::ifstream inputFile(filePath);
    std::vector<std::string> lines;

    if (!inputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }

    std::string commonPart = path + "/assets/";
    std::cout << "Ruta a reemplazar: " << commonPart << std::endl;
    std::string line;
    while (std::getline(inputFile, line)) {
        size_t found = line.find(commonPart);
        while (found != std::string::npos) {
            line.replace(found, commonPart.length(), "");
            found = line.find(commonPart, found);
        }
        lines.push_back(line);
    }

    inputFile.close();

    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
    }

    for (const std::string& newLine : lines) {
        outputFile << newLine << std::endl;
    }

    outputFile.close();

    std::cout << "Se han eliminado las ocurrencias de la cadena especificada." << std::endl;
 
}