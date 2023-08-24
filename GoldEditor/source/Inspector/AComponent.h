#pragma once
#include "../../../source/EngineBehaviour/GoldEngineLib.h"
#include "../UI/EditorUI/EditorGUI.h"
#include <iostream>


//CREATE COMPONENT INSPECTOR UI
class AComponent
{
public:
	virtual void start() = 0;

	template <typename T> void update(Entity* owner, int id) {
        if (owner->hasComponent<T>()) {
            ImGui::PushID(id);
            if (ImGui::Button("X")) {
                if (std::is_same<T, SpriteComponent>::value) {
                    std::cout << "El componente base no puede ser eliminado" << std::endl;
                }
                else {
                    owner->removeComponent<T>();
                }
            }
            else {
                draw(owner);
                ImGui::Separator();
            }
            ImGui::PopID();
        }

	}


	virtual void draw(Entity* owner) = 0;

public:
    static string RemoveDir(string fullPath) {
        std::string targetFolder = "assets/";

        // Encuentra la posición de la carpeta "assets" en la ruta
        size_t pos = fullPath.find(targetFolder);
        if (pos != std::string::npos) {
            // Extrae la parte de la ruta después de "assets"
            std::string extractedPath = fullPath.substr(pos + targetFolder.length());

            // Reemplazar barras diagonales normales por barras diagonales invertidas
            std::replace(extractedPath.begin(), extractedPath.end(), '/', '\\');

            return extractedPath;
        }

        return "";
    }
};