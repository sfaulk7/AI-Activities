#pragma once
#include "Scene.h"

class DecisionTreeScene :
    public Scene
{
public:
    void start() override;

    void makeDecision();

    void update(float deltaTime) override;
    void end() override;

private:


};