#include "UIImplement.h"

//IMGUI DOCKING NOT WORKING

void UIImplement::start() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 

#pragma region STYLE
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 4.0f;
	style->FramePadding = ImVec2(5.0f, 5.0f);
	style->FrameRounding = 4.0f;
	style->WindowPadding = ImVec2(4.0f, 4.0f);
	style->WindowBorderSize = 0.0f;
	style->IndentSpacing = 20.0f;
	style->Alpha = 1.0f;
	style->TabRounding = 5.0f;
	style->TabBorderSize = 0.0f;

	const ImVec4& color1 = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	const ImVec4& color2 = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	const ImVec4& color3 = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
	const ImVec4& color4 = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_WindowBg] = color2;
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_ChildBg] = color1;
	colors[ImGuiCol_PopupBg] = color1;

	colors[ImGuiCol_Tab] = color1;
	colors[ImGuiCol_TabHovered] = color3;
	colors[ImGuiCol_TabActive] = color2;
	colors[ImGuiCol_TabUnfocused] = color1;
	colors[ImGuiCol_TabUnfocusedActive] = color2;

	colors[ImGuiCol_Border] = color2;
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

	colors[ImGuiCol_FrameBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = color1;
	colors[ImGuiCol_FrameBgActive] = color1;

	colors[ImGuiCol_TitleBg] = color1;
	colors[ImGuiCol_TitleBgActive] = color1;
	colors[ImGuiCol_TitleBgCollapsed] = color1;

	colors[ImGuiCol_MenuBarBg] = color1;

	colors[ImGuiCol_Separator] = color1;
	colors[ImGuiCol_SeparatorHovered] = color3;
	colors[ImGuiCol_SeparatorActive] = color4;

	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_ScrollbarGrab] = color4;
	colors[ImGuiCol_ScrollbarGrabHovered] = color1;
	colors[ImGuiCol_ScrollbarGrabActive] = color4;

	colors[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);

	colors[ImGuiCol_Button] = color3;
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.55f, 0.55f, 0.60f);
	colors[ImGuiCol_ButtonActive] = color4;


	colors[ImGuiCol_Header] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.36f, 0.36f, 0.36f, 0.80f);

	colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);

	colors[ImGuiCol_DockingPreview] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
	colors[ImGuiCol_DockingEmptyBg] = color1;

	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);

	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);

	colors[ImGuiCol_TextSelectedBg] = color3;

	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);

	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
#pragma endregion

	ImGui_ImplGlfw_InitForOpenGL (StartEngineGraphics::window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}


void UIImplement::draw() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpace(1);
}

void UIImplement::DrawCanvas() {
	bool show;
	ImGui::ShowDemoWindow(&show);
	ImGui::Begin("TEST");
	if (ImGui::Button("CLICK ME!!!")) {
		std::cout << "BRUH" << std::endl;
	}
	ImGui::End();
}


void UIImplement::DrawData() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UIImplement::~UIImplement() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}