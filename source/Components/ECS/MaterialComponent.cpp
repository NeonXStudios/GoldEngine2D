#include "MaterialComponent.h"


void MaterialComponent::init() {
    RecompileShader();
}

void MaterialComponent::update() {

}

void MaterialComponent::draw() {
    //ourShader->use();
}

void MaterialComponent::clean() {

}

string MaterialComponent::serialize() {
    json DataToSave;

    DataToSave["vertex"] = VertexPath;
    DataToSave["fragment"] = FragmentPath;

    return DataToSave.dump();
}

void MaterialComponent::deserialize(std::string g, std::string path) {
    json componentData = json::parse(g);

    VertexPath = componentData["vertex"];
    FragmentPath = componentData["fragment"];

    RecompileShader();
}

void MaterialComponent::RecompileShader() {
    string newPathVertex = FileSystem::GetAsset(VertexPath);
    string newPathFrag = FileSystem::GetAsset(FragmentPath);

    ourShader = new Shader(newPathVertex.c_str(), newPathFrag.c_str());

    ourShader->use();

    std::cout << "Vertex Material: " << newPathVertex << std::endl;
    std::cout << "Fragment Material: " << newPathFrag << std::endl;
}