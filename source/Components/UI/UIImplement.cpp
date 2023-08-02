#include "UIImplement.h"

void UIImplement::start() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 


	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL (StartEngineGraphics::window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}


void UIImplement::draw() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UIImplement::DrawCanvas() {
	ImGui::DockSpaceOverViewport (nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
	ImGui::Begin(" ");
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