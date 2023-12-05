#include "CanvasUI.h"

void CanvasUI::start() {
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, AppSettings::RenderWidth, AppSettings::RenderHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer is not complete!" << std::endl;



    glGenTextures(1, &colorAndDepthTexture);
    glBindTexture(GL_TEXTURE_2D, colorAndDepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, AppSettings::RenderWidth, AppSettings::RenderHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Crear y configurar el renderbuffer de profundidad
    glGenRenderbuffers(1, &depthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, AppSettings::RenderWidth, AppSettings::RenderHeight);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glGenFramebuffers(1, &framebuffer);
}

void CanvasUI::draw() {
        ImGui::Begin("Canvas Editor", &isOpen);
  //      ImVec2 windowSize = ImVec2(AppSettings::RenderWidth, AppSettings::RenderHeight);

		//ImGui::Begin("Canvas Editor", &isOpen);
  //      ImVec2 windowPos = ImGui::GetWindowPos();
  //      ImVec2 offset = ImGui::GetWindowContentRegionMin();
  //      ImVec2 size = ImGui::GetContentRegionAvail();

  //      ImVec2 actualWindowSize = ImGui::GetWindowSize();
  //      float scaleFactor = std::min(actualWindowSize.x / windowSize.x, actualWindowSize.y / windowSize.y);
  //      imageSizeSCENE = ImVec2(AppSettings::RenderWidth * scaleFactor, AppSettings::RenderHeight * scaleFactor);


  //      // Calculamos la posición para centrar la imagen en la ventana
  //      imagePosition = ImVec2((actualWindowSize.x - imageSizeSCENE.x) * 0.5f, (actualWindowSize.y - imageSizeSCENE.y) * 0.5f);

  //      ImGui::SetCursorPos(imagePosition);

  //      int WindowXSize = imageSizeSCENE.x;
  //      int WindowYSize = imageSizeSCENE.y;
  //      imageSizeSCENE.x = WindowXSize;
  //      imageSizeSCENE.y = WindowYSize;

        //drawSquareInImGui();
        ImVec2 size(AppSettings::RenderWidth, AppSettings::RenderHeight);
        ImGui::GetWindowDrawList()->AddRect(ImGui::GetCursorScreenPos(), ImVec2(ImGui::GetCursorScreenPos().x + size.x, ImGui::GetCursorScreenPos().y + size.y), IM_COL32(255, 255, 255, 255));
		ImGui::End();


		ImGui::Begin("UI Tools");
		if (ImGui::Button("Button", ImVec2(ImGui::GetWindowSize().x, 20))) {

		}

		if (ImGui::Button("Text", ImVec2(ImGui::GetWindowSize().x, 20))) {

		}

		if (ImGui::Button("Slider", ImVec2(ImGui::GetWindowSize().x, 20))) {

		}

		if (ImGui::Button("Input Text", ImVec2(ImGui::GetWindowSize().x, 20))) {

		}
		ImGui::End();
}

void CanvasUI::update() {

}

void CanvasUI::lateupdate() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAndDepthTexture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
}

void CanvasUI::fixupdate() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Copiar el contenido del framebuffer en la textura
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBindTexture(GL_TEXTURE_2D, texture);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, AppSettings::RenderWidth, AppSettings::RenderHeight, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}