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
	m_currentState = 0; //(Wander)
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

void FiniteStateMachine::StateHandler()
{
	//Handles changing the states
	switch (m_currentState)
	{
	case STATE_WANDER:
		WanderStateBehavior();
		break;

	case STATE_SEEKERSEEK:
		SeekStateBehavior();
		break;

	case STATE_SEEKERSEEKANDPURSUE:
		SeekAndPursueStateBehavior();
		break;

	case STATE_RUNNERFLEE:
		FleeStateBehavior();
		break;
	case STATE_RUNNERFLEEANDEVADE:
		FleeAndEvadeStateBehavior();
		break;

	default:
		break;
	}
}

void FiniteStateMachine::WanderStateBehavior()
{
	//A check so that the state properly changes if the user uses the T keybind to activate/deactivate tag
	if (m_tagActive == true)
	{
		//Seeker or Runner
		if (m_isSeeker == true)
		{
			m_currentState = STATE_SEEKERSEEK;
		}
		else
		{
			m_currentState = STATE_RUNNERFLEEANDEVADE;
		}
	}

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

	//Show detectection range
	MathLibrary::Vector2 wanderCircle = ownerPosition + (getOwner()->getTransform()->getForward() * 200);
	DrawCircleLines(wanderCircle.x, wanderCircle.y, 200, BLUE);
	//Show current state
	DrawText("Agent status: Wander", 100, 40, 40, YELLOW);

	//Agent spots player and starts tag
	if (detectionDistance < 200)
	{
		m_tagActive = true;

		//Seeker or Runner
		if (m_isSeeker == true)
		{
			m_currentState = STATE_SEEKERSEEK;
		}
		else
		{
			m_currentState = STATE_RUNNERFLEEANDEVADE;
		}
	}

	//Start wandering
	m_agentOwner->DisableAllBehaviors(2);
	m_agentOwner->EnableBehavior(2);
}

void FiniteStateMachine::SeekStateBehavior()
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

	//Show current state
	DrawText("Agent status: Seek", 100, 40, 40, YELLOW);

	//Tags and changes the state when within a small distance
	if (distance < 40 && m_tagBackTimer <= 0)
	{
		m_collided = true;
		m_isSeeker = !(m_isSeeker);
		m_tagBackTimer = 2500;
		m_timeAsSeeker = 0;
		m_timeAsRunner = 0;
		m_currentState = STATE_RUNNERFLEEANDEVADE;
	}
	else
	{
		m_tagBackTimer--;
	}

	//Starts to speed up after chasing for a while (Swaps to SeekerSeekAndPursue)
	if (m_timeAsSeeker >= 25000)
	{
		m_currentState = STATE_SEEKERSEEKANDPURSUE;
	}

	m_timeAsSeeker++;
	m_agentOwner->DisableAllBehaviors(2);
	m_agentOwner->EnableBehavior(0);
}

void FiniteStateMachine::SeekAndPursueStateBehavior()
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

	//Show current state
	DrawText("Agent status: Seek and Pursue", 100, 40, 40, YELLOW);

	//Tags and changes the state when within a small distance
	if (distance < 40 && m_tagBackTimer <= 0)
	{
		m_collided = true;
		m_isSeeker = !(m_isSeeker);
		m_tagBackTimer = 2500;
		m_timeAsSeeker = 0;
		m_timeAsRunner = 0;
		m_currentState = STATE_RUNNERFLEEANDEVADE;
	}
	else
	{
		m_tagBackTimer--;
	}

	m_timeAsSeeker++;
	m_agentOwner->DisableAllBehaviors(2);
	m_agentOwner->EnableBehavior(0);
	m_agentOwner->EnableBehavior(3);

}

void FiniteStateMachine::FleeStateBehavior()
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

	//Show current state
	DrawText("Agent status: Flee", 100, 40, 40, YELLOW);

	//Tags and changes the state when within a small distance
	if (distance < 40 && m_tagBackTimer <= 0)
	{
		m_collided = true;
		m_isSeeker = !(m_isSeeker);
		m_tagBackTimer = 2500;
		m_timeAsSeeker = 0;
		m_timeAsRunner = 0;
		m_currentState = STATE_SEEKERSEEK;
	}
	else
	{
		m_tagBackTimer--;
	}

	m_timeAsRunner++;
	m_agentOwner->DisableAllBehaviors(2);
	m_agentOwner->EnableBehavior(1);


}

void FiniteStateMachine::FleeAndEvadeStateBehavior()
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

	//Show current state
	DrawText("Agent status: Flee and Evade", 100, 40, 40, YELLOW);

	//Tags and changes the state when within a small distance
	if (distance < 40 && m_tagBackTimer <= 0)
	{
		m_collided = true;
		m_isSeeker = !(m_isSeeker);
		m_tagBackTimer = 2500;
		m_timeAsSeeker = 0;
		m_timeAsRunner = 0;
		m_currentState = STATE_SEEKERSEEK;
	}
	else
	{
		m_tagBackTimer--;
	}

	//Starts to ease up on running away after a while (Swaps to RunnerFlee)
	if (m_timeAsRunner >= 25000)
	{
		m_currentState = STATE_RUNNERFLEE;
	}

	m_timeAsRunner++;
	m_agentOwner->DisableAllBehaviors(2);
	m_agentOwner->EnableBehavior(1);
	m_agentOwner->EnableBehavior(4);
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

		//Tell user that you can swap tag active
		DrawText("Press T to swap active or inactive", 100, 12, 20, YELLOW);
		//Swap tag to be active or inactive outside of normal function
		if (IsKeyPressed(KEY_T))
		{
			m_tagActive = !(m_tagActive);
			m_tagTimer = 0;
			m_tagBackTimer = 0;
			m_timeAsSeeker = 0;
			m_timeAsRunner = 0;

			if (m_tagActive == false)
			{
				m_currentState = STATE_WANDER;
			}
		}

		//Contains the finite state machine
		StateHandler();

		//If tag is active 
		// (These statements keep track of extra variable that dont fall into a
		//  state section for the finite state machine)
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

			//Show when you can tag
			if (m_tagBackTimer <= 0)
			{
				DrawCircle(ownerPosition.x, ownerPosition.y, 40, GREEN);
			}
			else
			{
				DrawCircle(ownerPosition.x, ownerPosition.y, 40, RED);
			}

			//Will change the state to wander when tag is over
			if (m_tagActive == false)
			{
				m_currentState = STATE_WANDER;
			}
		}
	}
}

