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
	m_agentOwner = owner;
	m_target = Target;
	m_targets.Add(Target);
}

void DecisionTreeComponent::AddAnotherTarget(Actor* NewTarget)
{
	Actor* ptr = dynamic_cast<Actor*>(NewTarget);
	if (ptr == nullptr)
	{

	}
	else
	{
		m_targets.Add(NewTarget);
	}
}

void DecisionTreeComponent::DisplayCurrentBehaviour()
{
	if (m_target->IsPredator())
	{
		DrawText("Target Status: Predator", 20, 90, 40, YELLOW);
	}
	else
	{
		DrawText("Target Status: Prey", 20, 90, 40, YELLOW);
	}

	//Wander if too far away
	if (m_currentState == STATE_WANDER)
	{
		//Show current state
		DrawText("Agent status: Wander", 20, 10, 40, YELLOW);
		DrawText(TextFormat("Target: %s", m_target->getName()), 20, 50, 40, YELLOW);
	}
	//Flee
	else if (m_currentState == STATE_FLEE)
	{
		//Show current state
		DrawText("Agent status: Flee", 20, 10, 40, YELLOW);
		DrawText(TextFormat("Target: %s", m_target->getName()), 20, 50, 40, YELLOW);
	}
	//Seek
	else if (m_currentState == STATE_SEEK)
	{
		//Show current state
		DrawText("Agent status: Seek", 20, 10, 40, YELLOW);
		DrawText(TextFormat("Target: %s", m_target->getName()), 20, 50, 40, YELLOW);
	}
}

int DecisionTreeComponent::DecideBehavior()
{
	MathLibrary::Vector2 ownerPosition = m_agentOwner->getTransform()->getLocalPosition();
	MathLibrary::Vector2 ownerVelocity = m_agentOwner->getTransform()->getVelocity();
	MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();
	MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
	float distance = distanceVector.getMagnitude();

	//Wander if too far away
	if (distance > 500)
	{
		m_currentState = STATE_WANDER;
		WanderStateBehavior();
	}
	else
	{
		//Flee
		if (m_target->IsPredator() == true)
		{
			m_currentState = STATE_FLEE;
			FleeStateBehavior();
		}
		//Seek
		else
		{
			m_currentState = STATE_SEEK;
			SeekStateBehavior();
		}
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
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		m_target->PredatorSwap();
	}

	if (IsKeyPressed(KEY_ZERO))
	{
		m_target = m_targets[0];
	}
	else if (IsKeyPressed(KEY_ONE))
	{
		m_target = m_targets[1];
	}
	else if (IsKeyPressed(KEY_TWO))
	{
		m_target = m_targets[2];
	}
	else if (IsKeyPressed(KEY_THREE))
	{
		m_target = m_targets[3];
	}
	else if (IsKeyPressed(KEY_FOUR))
	{
		m_target = m_targets[4];
	}
	else if (IsKeyPressed(KEY_FIVE))
	{
		m_target = m_targets[5];
	}

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