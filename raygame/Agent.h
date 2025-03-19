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

    /// <summary>
    /// Sets the behavior of the Agent with a number 0 - 5 <para />
    /// Agents behavior will be 0 (Seek) by default
    /// </summary>
    /// <param name="behavior">: The behavior the Agent will perform</param>
    /// <param name="Seek">: 0 </param>
    /// <param name="Flee">: 1 </param>
    /// <param name="Wander">: 2 </param>
    /// <param name="Persue">: 3 </param>
    /// <param name="Evade">: 4 </param>
    /// <param name="Arrive">: 5 </param>
    void EnableBehavior(int behavior);

    void DisableBehavior(int behavior);

    void EnableAllBehaviors();

    void DisableAllBehaviors(int count);

    bool GetBehaviorStatus(int behaviour);

    void EnableTag();
    void DisableTag();




private:
    //bool m_started;
    //Transform2D* m_transform;
    //Collider* m_collider;
    //DynamicArray<Component*> m_components;
};