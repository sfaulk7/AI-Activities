#pragma once
#include "Component.h"

class FleeComponent : public Component
{
public:
    FleeComponent() {}
    ~FleeComponent();
    /// <summary>
    /// Loads the given texture
    /// </summary>
    /// <param name="texture">Sets the sprites image to be the given texture</param>
    void ChangeTarget(Actor* NewTarget);
    FleeComponent(Actor* owner, Actor* target);

    void update(float deltaTime);
private:
    Actor* m_target;
};