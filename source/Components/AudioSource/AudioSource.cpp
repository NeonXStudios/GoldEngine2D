#include "AudioSource.h"
#include "nlohmann/json.hpp"

using namespace nlohmann;
using namespace std;

std::string AudioSource::serialize () {
    json componentData;
    componentData["pan"] = pan;
    float g;
    channel->getVolume(&g);
    componentData["volumen"] = g;
    componentData["pathfile"] = AudioPath;

    return componentData.dump();
}

void AudioSource::deserialize(std::string g) {
    json componentData = json::parse(g);
    SetPan  (componentData["pan"]);
    SetVolumen (componentData["volumen"]);
    AudioPath = componentData["pathfile"];
}