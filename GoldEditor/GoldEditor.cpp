#include <iostream>
#include "../source/Graphics/RunEngine.h"
#include <iostream>


int main()
{
    RunEngine* engine = new RunEngine();
    engine->StartGameEngine();

    std::cout << "Game finish" << endl;
    return 0;
}