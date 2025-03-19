#include "DecisionTreeComponent.h"
#include "Agent.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"


DecisionTreeComponent::~DecisionTreeComponent()
{
	SetDisabled();
}

DecisionTreeComponent::DecisionTreeComponent(Agent* owner, Actor* Target)
{
	m_currentState = 0;
	m_stateChangeCounter = 0;
	m_agentOwner = owner;
	m_target = Target;
}

void DecisionTreeComponent::ChangeTarget(Actor* NewTarget)
{
	m_target = NewTarget;
}

void DecisionTreeComponent::DisplayCurrentBehaviour()
{
	//Wander if too far away
	if (m_currentState == STATE_WANDER)
	{
		//Show current state
		DrawText("Agent status: Wander", 100, 40, 40, YELLOW);
		DrawText(TextFormat("Target: %s", m_target->getName()), 100, 80, 40, YELLOW);
	}

	//Flee if too close
	if (m_currentState == STATE_FLEE)
	{
		//Show current state
		DrawText("Agent status: Flee", 100, 40, 40, YELLOW);
		DrawText(TextFormat("Target: %s", m_target->getName()), 100, 80, 40, YELLOW);
	}

	//Seek if within distance
	if (m_currentState == STATE_SEEK)
	{
		//Show current state
		DrawText("Agent status: Seek", 100, 40, 40, YELLOW);
		DrawText(TextFormat("Target: %s", m_target->getName()), 100, 80, 40, YELLOW);
	}
}

int DecisionTreeComponent::DecideBehavior()
{
	MathLibrary::Vector2 ownerPosition = m_agentOwner->getTransform()->getLocalPosition();
	MathLibrary::Vector2 ownerVelocity = m_agentOwner->getTransform()->getVelocity();
	MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();
	MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
	float distance = distanceVector.getMagnitude();
	
	m_stateChangeCounter--;

	//Wander if too far away
	if (distance > 500 && m_stateChangeCounter <= 0)
	{
		if (m_stateChangeCounter <= 0)
		{
			m_stateChangeCounter = 5000;
		}
		m_currentState = STATE_WANDER;
		WanderStateBehavior();
		//Show current state
	}

	//Flee if too close
	if (distance <= 100 && m_stateChangeCounter <= 0)
	{
		if (m_stateChangeCounter <= 0)
		{
			m_stateChangeCounter = 5000;
		}
		m_currentState = STATE_FLEE;
		FleeStateBehavior();
		//Show current state
		DrawText("Agent status: Flee", 100, 40, 40, YELLOW);
	}

	//Seek if within distance
	if (distance <= 500 && m_stateChangeCounter <= 0)
	{
		if (m_stateChangeCounter <= 0)
		{
			m_stateChangeCounter = 5000;
		}
		m_currentState = STATE_SEEK;
		SeekStateBehavior();

		//Show current state
		DrawText("Agent status: Seek", 100, 40, 40, YELLOW);
	}


	return m_currentState;
}

void DecisionTreeComponent::WanderStateBehavior()
{
	//Puts the positions and the owner's velocity into variables for ease of use
	MathLibrary::Vector2 ownerPosition = m_agentOwner->getTransform()->getLocalPosition();
	MathLibrary::Vector2 ownerVelocity = m_agentOwner->getTransform()->getVelocity();
	MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();

	//Actual distance between owner and target
	MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
	float distance = distanceVector.getMagnitude();

	//Distance from owner to the circle used to wander
	distanceVector = targetPosition - (ownerPosition + (m_agentOwner->getTransform()->getForward() * 200));
	float detectionDistance = distanceVector.getMagnitude();

	//Show detectection range
	MathLibrary::Vector2 wanderCircle = ownerPosition + (m_agentOwner->getTransform()->getForward() * 200);
	DrawCircleLines(wanderCircle.x, wanderCircle.y, 200, BLUE);

	//Start wandering
	m_agentOwner->DisableAllBehaviors(2);
	m_agentOwner->EnableBehavior(0);
}

void DecisionTreeComponent::SeekStateBehavior()
{
	//Puts the positions and the owner's velocity into variables for ease of use
	MathLibrary::Vector2 ownerPosition = m_agentOwner->getTransform()->getLocalPosition();
	MathLibrary::Vector2 ownerVelocity = m_agentOwner->getTransform()->getVelocity();
	MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();

	//Actual distance between owner and target
	MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
	float distance = distanceVector.getMagnitude();

	//Distance from owner to the circle used to wander
	distanceVector = targetPosition - (ownerPosition + (m_agentOwner->getTransform()->getForward() * 200));
	float detectionDistance = distanceVector.getMagnitude();

	m_agentOwner->DisableAllBehaviors(2);
	m_agentOwner->EnableBehavior(1);
}

void DecisionTreeComponent::FleeStateBehavior()
{
	//Puts the positions and the owner's velocity into variables for ease of use
	MathLibrary::Vector2 ownerPosition = m_agentOwner->getTransform()->getLocalPosition();
	MathLibrary::Vector2 ownerVelocity = m_agentOwner->getTransform()->getVelocity();
	MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();

	//Actual distance between owner and target
	MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
	float distance = distanceVector.getMagnitude();

	//Distance from owner to the circle used to wander
	distanceVector = targetPosition - (ownerPosition + (m_agentOwner->getTransform()->getForward() * 200));
	float detectionDistance = distanceVector.getMagnitude();

	m_agentOwner->DisableAllBehaviors(2);
	m_agentOwner->EnableBehavior(2);
}

void DecisionTreeComponent::update(float deltaTime)
{

	if (GetEnabled() == true)
	{
		switch (m_currentTarget)
		{
		case 0: //Target 0 (mouse)
			DecideBehavior();
			DisplayCurrentBehaviour();
			break;

		case 1: //Target 1 (Top left)
			DecideBehavior();
			DisplayCurrentBehaviour();
			break;

		case 2: //Target 2 (Top Right)
			DecideBehavior();
			DisplayCurrentBehaviour();
			break;

		case 3: //Target 3 (Middle)
			DecideBehavior();
			DisplayCurrentBehaviour();
			break;

		case 4: //Target 4 (Bottom Left)
			DecideBehavior();
			DisplayCurrentBehaviour();
			break;

		case 5: //Target 5 (Bottom Right)
			DecideBehavior();
			DisplayCurrentBehaviour();
			break;
		}
	}
}