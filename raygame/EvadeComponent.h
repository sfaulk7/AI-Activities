#pragma once
#include "Component.h"

class EvadeComponent : public Component
{
public:
    EvadeComponent() {}
    ~EvadeComponent();

    EvadeComponent(Actor* owner, Actor* target);
    void ChangeTarget(Actor* target);

    void update(float deltaTime);
private:
    Actor* m_target;
};