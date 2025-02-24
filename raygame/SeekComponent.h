#pragma once
#include "Component.h"

class SeekComponent : public Component
{
public:
    SeekComponent() {}
    ~SeekComponent();

    SeekComponent(Actor* owner, Actor* target);

    void update(float deltaTime);
private:
    Actor* m_target;
};