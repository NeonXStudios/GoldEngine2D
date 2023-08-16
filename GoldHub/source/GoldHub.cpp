#include "GoldHub.h"

using namespace std;

int main ()
{
    GoldHub* hub = new GoldHub();
    RunEngine* engine = new RunEngine();


    engine->StartGameEngine (hub, false);

    return 0;
}