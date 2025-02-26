#include "ArriveComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"

ArriveComponent::~ArriveComponent()
{
	SetDisabled();
}

ArriveComponent::ArriveComponent(Actor* owner, Actor* Target) : Component(owner, "ArriveComponent")
{
	m_target = Target;
	this->SetDisabled();
}

ArriveComponent::ArriveComponent(Actor* owner, MathLibrary::Vector2 Target) : Component(owner, "ArriveComponent")
{
	m_target->getTransform()->setLocalPosition(Target);
	this->SetDisabled();
}

void ArriveComponent::update(float deltaTime)
{
	if (GetEnabled() == true)
	{
		//DrawText("CurrentBehavior: Arrive (5)", 100, 40, 40, YELLOW);

		//Puts the positions and the owner's velocity into variables for ease of use
		MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getLocalPosition();
		MathLibrary::Vector2 ownerVelocity = getOwner()->getTransform()->getVelocity();
		MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();

		//Display what it is chasing
		DrawLine(targetPosition.x, targetPosition.y, ownerPosition.x, ownerPosition.y, RED);

		//Calculates a vector from the owner to the target, then normalizes it
		MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
		float distance = distanceVector.getMagnitude();
		distanceVector.normalize();


		//Calculates the desiredVelocity
		MathLibrary::Vector2 desiredVelocity;
		DrawCircleLines(targetPosition.x, targetPosition.y, 750, YELLOW);
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
}

