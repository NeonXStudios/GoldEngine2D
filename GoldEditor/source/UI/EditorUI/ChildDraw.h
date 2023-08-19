#pragma once
#include <iostream>
#include "../../source/EngineBehaviour/GoldEngineLib.h"

using namespace std;


class ChildDraw
{
public:
	static bool isOpen;

	static void DrawChilds (Entity* object) {
        //if (object->childrens.size() > 0 && object->parent == nullptr /*&& isArrowButtonOpen[i] == true*/) {
        //    for (int e = 0; e < object->childrens.size(); e++) {
        //        ImGui::PushID(e);

        //        Entity* child = object->childrens[e];

        //        if (ImGui::Selectable(child->ObjectName.c_str())) {
        //            UIManager::instance->inspectorui->ObjectSelectToInspector = child;
        //            std::cout << "SELECT OBJECT: " << child->ObjectName << std::endl;
        //            SelectInHierarchy = true;
        //        }
        //        ImGui::PopID();
        //    }
        //}
	}
};