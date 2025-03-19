#pragma once
#include "Component.h"

class PursueComponent : public Component
{
public:
    PursueComponent() {}
    ~PursueComponent();

    PursueComponent(Actor* owner, Actor* target);
    void ChangeTarget(Actor* target);

    void update(float deltaTime);
private:
    Actor* m_target;
};