#pragma once
#include "Component.h"

class BehaviourComponent : public Component
{
public:
    BehaviourComponent() {}
    ~BehaviourComponent();

    BehaviourComponent(Agent* owner);

    void update(float deltaTime);
private:
    Agent* m_agentOwner;
    int m_currentBehavior;
    int m_selectionBoxPosition;
};