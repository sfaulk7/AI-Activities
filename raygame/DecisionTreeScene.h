#pragma once
#include "Scene.h"
class DecisionTreeScene :
    public Scene
{
public:
    void start() override;
    void update(float deltaTime) override;

    Actor* fill;
    Actor* Mouse;
    Actor* Target1;
    Actor* Target2;
    Actor* Target3;
    Actor* Target4;
    Actor* Target5;
    Agent* Enemy;
};

