#pragma once
#include "Component.h"

class SeekComponent : public Component
{
public:
    SeekComponent() {}
    ~SeekComponent();

    void ChangeTarget(Actor* NewTarget);
    SeekComponent(Actor* owner, Actor* target);

    void update(float deltaTime);
private:
    Actor* m_target;
};