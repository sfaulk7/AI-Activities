#pragma once
#include "Component.h"

class FiniteStateMachine : public Component
{
public:
    FiniteStateMachine() {}
    ~FiniteStateMachine();

    FiniteStateMachine(Agent* owner, Actor* Target);

    void update(float deltaTime);
private:
    int m_currentState;
    Agent* m_agentOwner;
    Actor* m_target;
    bool m_tagActive;
    bool m_collided;
    bool m_isSeeker;
    int m_tagTimer;
    int m_tagBackTimer;
    int m_timeAsSeeker;
    int m_timeAsRunner;
};