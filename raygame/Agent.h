#pragma once
#include "Actor.h"

class Agent : public Actor
{
public:
    Agent();
    ~Agent();

    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="name">The name of this actor.</param>
    Agent(float x, float y, const char* name);

private:
    bool m_started;
    Transform2D* m_transform;
    Collider* m_collider;
    DynamicArray<Component*> m_components;
};