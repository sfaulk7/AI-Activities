#pragma once
#include "Component.h"

class WanderComponent : public Component
{
public:
    WanderComponent() {}
    ~WanderComponent();

    WanderComponent(Actor* owner);

    void update(float deltaTime);
private:
};