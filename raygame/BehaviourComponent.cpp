#include "BehaviourComponent.h"
#include "Agent.h"
//#include "Actor.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"

BehaviourComponent::~BehaviourComponent()
{
	SetDisabled();
}

BehaviourComponent::BehaviourComponent(Agent* owner) : Component(owner, "BehaviourComponent")
{
	m_agentOwner = owner;
	m_currentBehavior = 0;
	m_agentOwner->SetBehavior(m_currentBehavior);
	this->SetEnabled();
}

void BehaviourComponent::update(float deltaTime)
{
	if (GetEnabled() == true)
	{
		if (IsKeyPressed(KEY_A))
		{
			if (m_currentBehavior <= 0)
			{
				m_currentBehavior = 5;
				m_agentOwner->SetBehavior(m_currentBehavior);
			}
			else
			{
				m_currentBehavior--;
				m_agentOwner->SetBehavior(m_currentBehavior);
			}
		}
		if (IsKeyPressed(KEY_D))
		{
			if (m_currentBehavior >= 5)
			{
				m_currentBehavior = 0;
				m_agentOwner->SetBehavior(m_currentBehavior);
			}
			else
			{
				m_currentBehavior++;
				m_agentOwner->SetBehavior(m_currentBehavior);
			}
		}

		/*switch (m_currentBehavior)
		{
		case 0:
			DrawText("CurrentBehavior: Seek (0)", 100, 40, 40, YELLOW);
			break;
		case 1:
			DrawText("CurrentBehavior: Flee (1)", 100, 40, 40, YELLOW);
			break;
		case 2:
			DrawText("CurrentBehavior: Wander (2)", 100, 40, 40, YELLOW);
			break;
		case 3:
			DrawText("CurrentBehavior: Pursue (3)", 100, 40, 40, YELLOW);
			break;
		case 4:
			DrawText("CurrentBehavior: Evade (4)", 100, 40, 40, YELLOW);
			break;
		case 5:
			DrawText("CurrentBehavior: Arrive (5)", 100, 40, 40, YELLOW);
			break;
		}*/
	}
}

