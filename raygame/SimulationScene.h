#pragma once
#include "Scene.h"

class SimulationScene :
    public Scene
{
public:
    void start() override;
    void update(float deltaTime) override;
    void end() override;

private:

};