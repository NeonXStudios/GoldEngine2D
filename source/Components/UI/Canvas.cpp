#include "Canvas.h"


void Canvas::init() {
    Data.push_back(new UIButton());

    for (UIBehaviour* g : Data) {
        g->start();
    }
}

void Canvas::draw() {
    for (UIBehaviour* g : Data) {
        g->draw();
        //std::cout << "Total canvas obj " << Data.size() << std::endl;
    }
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
