#pragma once
#include <iostream>
using namespace std;

class EngineBehaviour
{
public:
    string GamePath = "";
    virtual void start() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void lateupdate() = 0;
    virtual void fixupdate() = 0;
    virtual void release() = 0;
    virtual void drawUI() = 0;
    //virtual void createInstance() = 0;
    //virtual void releaseInstance() = 0;
};