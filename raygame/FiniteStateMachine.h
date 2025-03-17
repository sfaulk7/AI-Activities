#pragma once
#include "Component.h"

enum State
{
    STATE_WANDER,
    STATE_SEEKERSEEK,
    STATE_SEEKERSEEKANDPURSUE,
    STATE_RUNNERFLEE,
    STATE_RUNNERFLEEANDEVADE
};

class FiniteStateMachine : public Component
{
public:
    FiniteStateMachine() {}
    ~FiniteStateMachine();

    FiniteStateMachine(Agent* owner, Actor* Target);

    void StateHandler();
    void WanderStateBehavior();
    void SeekStateBehavior();
    void SeekAndPursueStateBehavior();
    void FleeStateBehavior();
    void FleeAndEvadeStateBehavior();
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