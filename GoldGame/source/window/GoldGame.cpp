#include "GoldGame.h"

#include <iostream>
#include <GoldEngineLib.h>

int main()
{
    GoldGame* gm = new GoldGame();
    RunEngine* engine = new RunEngine();
    engine->StartGameEngine (gm, true);
}