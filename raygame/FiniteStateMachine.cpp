#include "FiniteStateMachine.h"
#include "Agent.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"

FiniteStateMachine::~FiniteStateMachine()
{
	SetDisabled();
}

FiniteStateMachine::FiniteStateMachine(Agent* owner, Actor* Target) : Component(owner, "FiniteStateMachine")
{
	m_currentState = 2; //(Wander)
	m_agentOwner = owner;
	m_target = Target;
	m_tagActive = false;
	m_collided = false;
	m_isSeeker = true;
	m_tagTimer = 0;
	m_tagBackTimer = 0;
	m_timeAsSeeker = 0;
	m_timeAsRunner = 0;
}

void FiniteStateMachine::update(float deltaTime)
{
	if (GetEnabled() == true)
	{
		//Puts the positions and the owner's velocity into variables for ease of use
		MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getLocalPosition();
		MathLibrary::Vector2 ownerVelocity = getOwner()->getTransform()->getVelocity();
		MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();

		//Actual distance between owner and target
		MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
		float distance = distanceVector.getMagnitude();

		//Distance from owner to the circle used to wander
		distanceVector = targetPosition - (ownerPosition + (getOwner()->getTransform()->getForward() * 200));
		float detectionDistance = distanceVector.getMagnitude();

		//If tag is active
		if (m_tagActive == true)
		{
			//Counter until tag is over
			DrawText(TextFormat("TagTimer: %i", m_tagTimer), 100, 80, 40, YELLOW);
			if (distance > 200)
			{
				m_tagTimer++;
				if (m_tagTimer >= 100000)
				{
					m_tagTimer = 0;
					m_tagActive = false;
				}
			}

			//Shows how far you need to be in order for the tagtimer to increment
			DrawCircleLines(ownerPosition.x, ownerPosition.y, 200, BLUE);

			//Agent and player come close enough to count as a tag
			if (distance < 40 && m_tagBackTimer <= 0)
			{
				m_collided = true;
				m_isSeeker = !(m_isSeeker);
				m_tagBackTimer = 2500;
				m_timeAsSeeker = 0;
				m_timeAsRunner = 0;
			}
			else
			{
				m_tagBackTimer--;
			}

			//Show when you can tag
			if (m_tagBackTimer <= 0)
			{
				DrawCircle(ownerPosition.x, ownerPosition.y, 40, GREEN);
			}
			else
			{
				DrawCircle(ownerPosition.x, ownerPosition.y, 40, RED);
			}

			//Seeker Statement
			if (m_isSeeker == true)
			{
				//Starts to speed up after chasing for a while
				if (m_timeAsSeeker >= 25000)
				{
					m_currentState = 3;
				}
				else
				{
					m_currentState = 0;
				}

				//The two seeker scenarios
				switch (m_currentState)
				{
				case 0: // Seek
					m_timeAsSeeker++;
					m_agentOwner->DisableAllBehaviors();
					m_agentOwner->EnableBehavior(0);
					DrawText("Agent status: Seek", 100, 40, 40, YELLOW);
					break;
				case 3: // Seek and Pursue
					m_timeAsSeeker++;
					m_agentOwner->DisableAllBehaviors();
					m_agentOwner->EnableBehavior(0);
					m_agentOwner->EnableBehavior(3);
					DrawText("Agent status: Seek and Pursue", 100, 40, 40, YELLOW);
					break;
				}
			}
			//Runner Statement
			else
			{
				//Starts to ease up on running away after a while
				if (m_timeAsRunner >= 25000)
				{
					m_currentState = 1;
				}
				else
				{
					m_currentState = 4;
				}

				//The two runner scenarios
				switch (m_currentState)
				{
				case 1: // Flee
					m_timeAsRunner++;
					m_agentOwner->DisableAllBehaviors();
					m_agentOwner->EnableBehavior(1);
					DrawText("Agent status: Flee", 100, 40, 40, YELLOW);
					break;
				case 4: // Flee and Evade
					m_timeAsRunner++;
					m_agentOwner->DisableAllBehaviors();
					m_agentOwner->EnableBehavior(1);
					m_agentOwner->EnableBehavior(4);
					DrawText("Agent status: Flee and Evade", 100, 40, 40, YELLOW);
					break;
				}
			}
		}
		//If tag isn't active
		else
		{
			//Show detectection range
			MathLibrary::Vector2 wanderCircle = ownerPosition + (getOwner()->getTransform()->getForward() * 200);
			DrawCircleLines(wanderCircle.x, wanderCircle.y, 200, BLUE);

			//Agent spots player and starts tag
			if (detectionDistance < 200)
			{
				m_tagActive = true;
			}

			DrawText("Agent status: Wander", 100, 40, 40, YELLOW);

			//Start wandering
			m_agentOwner->DisableAllBehaviors();
			m_agentOwner->EnableBehavior(2);
		}
	}
}

