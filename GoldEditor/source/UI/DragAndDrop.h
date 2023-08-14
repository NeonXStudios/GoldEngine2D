#pragma once
#include <iostream>
#include <imgui.h>

using namespace std;

class DragAndDrop
{
public:
	static void dragStart(string ID, string PathToSend, string MoveDataNAme) {
        ImGuiDragDropFlags src_flags = 0;
        src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
        src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging

        if (ImGui::BeginDragDropSource(src_flags))
        {
            const char* filePathN;
            string t = "Moving " + MoveDataNAme;
            ImGui::Text(t.c_str());

            std::string pathToSend = PathToSend;
            ImGui::SetDragDropPayload(PathToSend.c_str(), pathToSend.c_str(), pathToSend.size() + 1);
            ImGui::EndDragDropSource();
        }
	}
};