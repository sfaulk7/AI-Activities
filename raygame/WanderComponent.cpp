#include "WanderComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"
#include "random"
#include "ArriveComponent.h"

WanderComponent::~WanderComponent()
{
	SetDisabled();
}

WanderComponent::WanderComponent(Actor* owner) : Component(owner, "WanderComponent")
{
	this->SetDisabled();
	m_wandered = true;
	m_count = 0;
	//Set scaler / distance that can wander
	m_scale = 200;

	MathLibrary::Vector2 wanderPosition = { 1, 1 };
	MathLibrary::Vector2 wanderCircle = { 1, 1 };
}

void WanderComponent::Arrive(MathLibrary::Vector2 Target, float deltaTime)
{
	//Puts the positions and the owner's velocity into variables for ease of use
	MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getLocalPosition();
	MathLibrary::Vector2 ownerVelocity = getOwner()->getTransform()->getVelocity();

	//Display what it is chasing
	DrawLine(Target.x, Target.y, ownerPosition.x, ownerPosition.y, RED);

	//Calculates a vector from the owner to the target, then normalizes it
	MathLibrary::Vector2 distanceVector = Target - ownerPosition;
	float distance = distanceVector.getMagnitude();
	distanceVector.normalize();


	//Calculates the desiredVelocity
	MathLibrary::Vector2 desiredVelocity;
	DrawCircleLines(Target.x, Target.y, 750, YELLOW);
	if (distance < 750)
	{
		desiredVelocity = ((distanceVector * getOwner()->getTransform()->getMaxVelocity()) * (distance / 2000));
	}
	else
	{
		desiredVelocity = distanceVector * getOwner()->getTransform()->getMaxVelocity();
	}


	//Calculates the Steering force
	MathLibrary::Vector2 steeringForce = desiredVelocity - ownerVelocity;

	//Sets the new velocity
	getOwner()->getTransform()->setVelocity(ownerVelocity + (steeringForce * deltaTime));

	//Sets the new position
	getOwner()->getTransform()->setLocalPosition(ownerPosition + (ownerVelocity * deltaTime));

	//Sets the new rotation
	getOwner()->getTransform()->setRotation(atan2(ownerVelocity.x, ownerVelocity.y));
	getOwner()->getTransform()->rotate(-1.57);
}

void WanderComponent::update(float deltaTime)
{
	if (GetEnabled() == true)
	{
		//DrawText("CurrentBehavior: Wander (2)", 100, 40, 40, YELLOW);

		//Puts the positions and the owner's velocity into variables for ease of use
		MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getLocalPosition();
		MathLibrary::Vector2 ownerVelocity = getOwner()->getTransform()->getVelocity();
		
		if (m_wandered == true)
		{
			//Get the wander positions x and y values
			float x = GetRandomValue(-10, 10);
			float y = GetRandomValue(-10, 10);

			//Set the wanderPosition
			wanderPosition = { x, y };
			wanderPosition.normalize();
			wanderPosition = wanderPosition * m_scale;
			wanderPosition = wanderPosition + ownerPosition;
			wanderPosition = wanderPosition + (getOwner()->getTransform()->getForward() * m_scale);

			//Set the wanderCircle
			wanderCircle = ownerPosition + (getOwner()->getTransform()->getForward() * m_scale);

			//Adjusts the wanderPosition to prevent the Agent from going off screen
			if (wanderPosition.x >= GetScreenWidth())
				wanderPosition.x -= 500;

			if (wanderPosition.x <= 0)
				wanderPosition.x += 500;

			if (wanderPosition.y >= GetScreenHeight())
				wanderPosition.y -= 500;

			if (wanderPosition.y <= 0)
				wanderPosition.y += 500;

			m_wandered = false;
		}

		if (m_wandered == false)
		{
			Arrive(wanderPosition, deltaTime);
			m_count++;
			if (m_count >= 25000)
			{
				m_wandered = true;
				m_count = 0;
			}
		}

		//Display the wanderCircle
		DrawCircleLines(wanderCircle.x, wanderCircle.y, m_scale, YELLOW);

		//Display what it is wandering to
		DrawLine(wanderPosition.x, wanderPosition.y, ownerPosition.x, ownerPosition.y, RED);
	}
}

