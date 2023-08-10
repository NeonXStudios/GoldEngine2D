#pragma once
#include <fstream>
#include <iostream>
#include "imgui.h"
#include "../../source/EngineBehaviour/GoldEngineLib.h"

class ScriptEditor
{
	Entity* own;
	std::string filePath;
	std::string fileContent;


public:
	ScriptEditor(Entity* owner) {
		own = owner;

		filePath = owner->getComponent<ScriptCompiler>().pathScript;
		fileContent;

		LoadFileContent(filePath, fileContent);

		std::cout << "FILE CONTENT LOAD " << std::endl << fileContent << std::endl;
	}


	void update() {
		ImGui::Begin ("SCRIPT EDITOR");
		ScriptCompiler* script = &own->getComponent<ScriptCompiler>();
		char str_hold[2048] = "";
		strcpy_s(str_hold, fileContent.c_str());
		ImVec2 Size;
		Size.x = ImGui::GetContentRegionAvail().x - 20;
		Size.y = ImGui::GetContentRegionAvail().y - 20;

		if (ImGui::InputTextMultiline("-", str_hold, 999999, Size)) {
			fileContent = (string)str_hold;
			SaveFileContent(filePath, fileContent);
		}

		ImGui::End   ();
	}

	void SaveFileContent(const std::string& filename, const std::string& content) {
		std::ofstream archivo("game/assets/" + filename + ".sr"); // Abre el archivo en modo de escritura

		if (!archivo.is_open()) {
			std::cerr << "No se pudo abrir el archivo." << std::endl;
		}

		archivo << content << std::endl;

		archivo.close(); // Cierra el archivo
	}

	void LoadFileContent(const std::string& filename, std::string& content) {
		std::ifstream scrpt("game/assets/" + filename + ".sr");


		if (!scrpt.is_open()) {
			std::cerr << "No se pudo abrir el archivo de la ruta: " << filename << std::endl;
		}



		std::string contenido((std::istreambuf_iterator<char>(scrpt)),
			(std::istreambuf_iterator<char>()));

		content = contenido;
		scrpt.close();

	}
};