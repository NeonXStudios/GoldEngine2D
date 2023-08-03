#pragma once
class EngineBehaviour
{
public:
    virtual void start() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void release() = 0;
};