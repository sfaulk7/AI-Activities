#pragma once
#include "Component.h"

class PlayerVelocityComponent : public Component
{
public:
    PlayerVelocityComponent() {}
    ~PlayerVelocityComponent();
    /// <summary>
    /// Loads the given texture
    /// </summary>
    /// <param name="texture">Sets the sprites image to be the given texture</param>
    PlayerVelocityComponent(Actor* owner);

    void update(float deltaTime);
private:
    Actor* m_target;
};