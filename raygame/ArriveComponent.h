#pragma once
#include "Component.h"
#include "Transform2D.h"

class ArriveComponent : public Component
{
public:
    ArriveComponent() {}
    ~ArriveComponent();

    ArriveComponent(Actor* owner, Actor* Target);
    ArriveComponent(Actor* owner, MathLibrary::Vector2 Target);

    void update(float deltaTime);
private:
    Actor* m_target;
};