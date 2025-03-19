#pragma once
#include "Component.h"

enum State
{
    STATE_WANDER,
    STATE_SEEK,
    STATE_FLEE,
    STATE_ARRIVE
};

class DecisionTreeComponent : public Component
{
public:
    DecisionTreeComponent() {}
    ~DecisionTreeComponent();

    DecisionTreeComponent(Agent* owner, Actor* Target);
    
    void ChangeTarget(Actor* NewTarget);
    void DisplayCurrentBehaviour();
    int DecideBehavior();
    void WanderStateBehavior();
    void SeekStateBehavior();
    void FleeStateBehavior();
    void ArriveStateBehavior();
    void update(float deltaTime);

private:
    int m_stateChangeCounter;
    int m_currentState;
    Agent* m_agentOwner;
    Actor* m_target;
    int m_currentTarget;
};