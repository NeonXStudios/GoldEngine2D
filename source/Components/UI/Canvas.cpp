#include "Canvas.h"


void Canvas::init() {
    //glGenFramebuffers(1, &framebuffer);
    //glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, AppSettings::RenderWidth, AppSettings::RenderHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    //if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    //    std::cout << "Framebuffer is not complete!" << std::endl;



    //glGenTextures(1, &colorAndDepthTexture);
    //glBindTexture(GL_TEXTURE_2D, colorAndDepthTexture);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, AppSettings::RenderWidth, AppSettings::RenderHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //// Crear y configurar el renderbuffer de profundidad
    //glGenRenderbuffers(1, &depthRenderbuffer);
    //glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
    //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, AppSettings::RenderWidth, AppSettings::RenderHeight);


    //glBindFramebuffer(GL_FRAMEBUFFER, 0);


    // Inicializar tus elementos UI, como UIButton
    Data.push_back(new UIButton());
    for (UIBehaviour* g : Data) {
        g->start();
    }
}

void Canvas::draw() {
    for (UIBehaviour* g : Data) {
        g->draw();
    }
}

void Canvas::PreRender() {
    //glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAndDepthTexture, 0);
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
}

void Canvas::PostRender() {
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //// Copiar el contenido del framebuffer en la textura
    //glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, AppSettings::RenderWidth, AppSettings::RenderHeight, 0);
    //glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}


void Canvas::update() {

}

void Canvas::clean() {

}

string Canvas::serialize() {
    json CanvasData;

    return CanvasData.dump();
}




void Canvas::deserialize(std::string g, std::string path) {
    json data = json::parse(g);
}
