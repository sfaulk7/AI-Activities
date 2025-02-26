#pragma once
#include "Component.h"
#include "Transform2D.h"

class WanderComponent : public Component
{
public:
    WanderComponent() {}
    ~WanderComponent();

    WanderComponent(Actor* owner);

    void Arrive(MathLibrary::Vector2 Target, float deltaTime);

    void update(float deltaTime);
private:
    bool m_wandered;
    int m_count;
    int m_scale;
    MathLibrary::Vector2 wanderPosition;
    MathLibrary::Vector2 wanderCircle;
};