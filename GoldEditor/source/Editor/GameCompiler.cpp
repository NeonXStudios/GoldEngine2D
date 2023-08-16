#include "GameCompiler.h"
#include "GoldEditor.h"
#include <iostream>

#include <filesystem>
#include <nlohmann/json.hpp>


using namespace nlohmann;
using namespace std;


void GameCompiler::compileWindow()
{
    std::string folderName = GoldEditor::editor->ProjectPath + "/GameBuild/";

    if (fs::create_directory(folderName)) {
        std::cout << "Carpeta creada exitosamente." << std::endl;
    }
    else {
        std::cerr << "Error al crear la carpeta." << std::endl;
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

    std::cout << "Game compiled... (PLATAFORM WINDOW)" << std::endl;

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
}