#pragma once
#include "DynamicArray.h"
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
    
    void AddAnotherTarget(Actor* NewTarget);

    void DisplayCurrentBehaviour();
    int DecideBehavior();
    void WanderStateBehavior();
    void SeekStateBehavior();
    void FleeStateBehavior();
    Actor* CurrentTarget() { return m_target; }

    void update(float deltaTime);

private:
    int m_currentState;
    Agent* m_agentOwner;
    Actor* m_target;
    int m_currentTarget;
    DynamicArray<Actor*> m_targets;
};