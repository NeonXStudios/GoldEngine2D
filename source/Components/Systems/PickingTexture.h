#pragma once
#include "../../EngineBehaviour/GoldEngineLib.h"
#include <iostream>
using namespace std;

class PickingTexture
{
public:
    PickingTexture() {}

    ~PickingTexture();

    void Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void EnableWriting();

    void DisableWriting();

    struct PixelInfo {
        uint ObjectID = 0;
        uint DrawID = 0;
        uint PrimID = 0;

        void Print()
        {
            printf("Object %d draw %d prim %d\n", ObjectID, DrawID, PrimID);
        }
    };

    PixelInfo ReadPixel(unsigned int x, unsigned int y);

private:
    GLuint m_fbo = 0;
    GLuint m_pickingTexture = 0;
    GLuint m_depthTexture = 0;
};