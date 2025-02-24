#pragma once
#include "Component.h"

class ArriveComponent : public Component
{
public:
    ArriveComponent() {}
    ~ArriveComponent();

    ArriveComponent(Actor* owner, Actor* target);

    void update(float deltaTime);
private:
    Actor* m_target;
};