#pragma once
#include "Component.h"

class SeekComponent : public Component
{
public:
    SeekComponent() {}
    ~SeekComponent();
    /// <summary>
    /// Loads the given texture
    /// </summary>
    /// <param name="texture">Sets the sprites image to be the given texture</param>
    SeekComponent(Actor* owner, Actor* target);

    void update(float deltaTime) override;
private:
    Actor* m_target;
};