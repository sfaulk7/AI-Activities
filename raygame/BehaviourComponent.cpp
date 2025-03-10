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
	m_agentOwner->DisableAllBehaviors();
	m_agentOwner->EnableBehavior(m_currentBehavior);
	this->SetEnabled();

	m_selectionBoxPosition = 0;
}

void BehaviourComponent::update(float deltaTime)
{
	if (GetEnabled() == true)
	{
		//Controls text
		DrawText("A and D to cycle", 10, 50, 10, YELLOW);
		DrawText("Q to disable and E to enable", 10, 60, 10, YELLOW);
		DrawText("Z to disable ALL and C to enable ALL", 10, 70, 10, YELLOW);

		//Seek text (0)
		DrawText("SeekBehaviour", 10, 10, 10, YELLOW);
		if (m_agentOwner->GetBehaviorStatus(0) == false)
		{
			DrawText("OFF", 10, 30, 10, YELLOW);
		}
		else
		{
			DrawText("ON", 10, 30, 10, YELLOW);
		}

		//Flee text (1)
		DrawText("FleeBehaviour", 110, 10, 10, YELLOW);
		if (m_agentOwner->GetBehaviorStatus(1) == false)
		{
			DrawText("OFF", 110, 30, 10, YELLOW);
		}
		else
		{
			DrawText("ON", 110, 30, 10, YELLOW);
		}

		//Wander text (2)
		DrawText("WanderBehaviour", 210, 10, 10, YELLOW);
		if (m_agentOwner->GetBehaviorStatus(2) == false)
		{
			DrawText("OFF", 210, 30, 10, YELLOW);
		}
		else
		{
			DrawText("ON", 210, 30, 10, YELLOW);
		}

		//Pursue text (3)
		DrawText("PursueBehaviour", 310, 10, 10, YELLOW);
		if (m_agentOwner->GetBehaviorStatus(3) == false)
		{
			DrawText("OFF", 310, 30, 10, YELLOW);
		}
		else
		{
			DrawText("ON", 310, 30, 10, YELLOW);
		}

		//Evade text (4)
		DrawText("EvadeBehaviour", 410, 10, 10, YELLOW);
		if (m_agentOwner->GetBehaviorStatus(4) == false)
		{
			DrawText("OFF", 410, 30, 10, YELLOW);
		}
		else
		{
			DrawText("ON", 410, 30, 10, YELLOW);
		}

		//Arrive text (5)
		DrawText("ArriveBehaviour", 510, 10, 10, YELLOW);
		if (m_agentOwner->GetBehaviorStatus(5) == false)
		{
			DrawText("OFF", 510, 30, 10, YELLOW);
		}
		else
		{
			DrawText("ON", 510, 30, 10, YELLOW);
		}

		//SelectionBox
		DrawRectangleLines(m_selectionBoxPosition + 5, 5, 100, 40, YELLOW);

		//Cycle between the behaviors
		if (IsKeyPressed(KEY_A))
		{
			if (m_selectionBoxPosition <= 0)
				m_selectionBoxPosition = 500;
			else
				m_selectionBoxPosition -= 100;

			/*if (m_currentBehavior <= 0)
			{
				m_currentBehavior = 5;
				m_agentOwner->SetBehavior(m_currentBehavior);
			}
			else
			{
				m_currentBehavior--;
				m_agentOwner->SetBehavior(m_currentBehavior);
			}*/
		}
		if (IsKeyPressed(KEY_D))
		{
			if (m_selectionBoxPosition >= 500)
				m_selectionBoxPosition = 0;
			else
				m_selectionBoxPosition += 100;


			/*if (m_currentBehavior >= 5)
			{
				m_currentBehavior = 0;
				m_agentOwner->SetBehavior(m_currentBehavior);
			}
			else
			{
				m_currentBehavior++;
				m_agentOwner->SetBehavior(m_currentBehavior);
			}*/
		}

		//Disable currently selected behavior
		if(IsKeyPressed(KEY_Q))
		{
			switch (m_selectionBoxPosition)
			{
			case 0: // Seek
				m_agentOwner->DisableBehavior(0);
				break;
			case 100: // Flee
				m_agentOwner->DisableBehavior(1);
				break;
			case 200: // Wander
				m_agentOwner->DisableBehavior(2);
				break;
			case 300: // Pursue
				m_agentOwner->DisableBehavior(3);
				break;
			case 400: // Evade
				m_agentOwner->DisableBehavior(4);
				break;
			case 500: // Arrive
				m_agentOwner->DisableBehavior(5);
				break;
			}
		}
		//Enable currently selected behavior
		if (IsKeyPressed(KEY_E))
		{
			switch (m_selectionBoxPosition)
			{
			case 0: // Seek
				m_agentOwner->EnableBehavior(0);
				break;
			case 100: // Flee
				m_agentOwner->EnableBehavior(1);
				break;
			case 200: // Wander
				m_agentOwner->EnableBehavior(2);
				break;
			case 300: // Pursue
				m_agentOwner->EnableBehavior(3);
				break;
			case 400: // Evade
				m_agentOwner->EnableBehavior(4);
				break;
			case 500: // Arrive
				m_agentOwner->EnableBehavior(5);
				break;
			}
		}

		//Disable all behaviors
		if (IsKeyPressed(KEY_Z))
		{
			m_agentOwner->DisableAllBehaviors();
		}
		//Enable all behaviors
		if (IsKeyPressed(KEY_C))
		{
			m_agentOwner->EnableAllBehaviors();
		}

		//If a number 0-5 is pressed on the keyboard set the behavior to be the corresponding number
		switch (GetKeyPressed())
		{
		case KeyboardKey(KEY_ZERO): // Seek
			m_selectionBoxPosition = 0;
			//m_agentOwner->SetBehavior(0);
			break;
		case KeyboardKey(KEY_ONE): // Flee
			m_selectionBoxPosition = 100;
			//m_agentOwner->SetBehavior(1);
			break;
		case KeyboardKey(KEY_TWO): // Wander
			m_selectionBoxPosition = 200;
			//m_agentOwner->SetBehavior(2);
			break;
		case KeyboardKey(KEY_THREE): // Pursue
			m_selectionBoxPosition = 300;
			//m_agentOwner->SetBehavior(3);
			break;
		case KeyboardKey(KEY_FOUR): // Evade
			m_selectionBoxPosition = 400;
			//m_agentOwner->SetBehavior(4);
			break;
		case KeyboardKey(KEY_FIVE): // Arrive
			m_selectionBoxPosition = 500;
			//m_agentOwner->SetBehavior(5);
			break;
		}
	}
}

