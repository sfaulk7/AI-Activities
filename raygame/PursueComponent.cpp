#include "PursueComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"

PursueComponent::~PursueComponent()
{
	SetDisabled();
}

PursueComponent::PursueComponent(Actor* owner, Actor* Target) : Component(owner, "PursueComponent")
{
	m_target = Target;
	this->SetDisabled();
}

void PursueComponent::ChangeTarget(Actor* target)
{
	m_target = target;
}

void PursueComponent::update(float deltaTime)
{
	if (this->GetEnabled() == true)
	{
		//DrawText("CurrentBehavior: Pursue (3)", 100, 40, 40, YELLOW);

		//Puts the positions and the owner's velocity into variables for ease of use
		MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getLocalPosition();
		MathLibrary::Vector2 ownerVelocity = getOwner()->getTransform()->getVelocity();
		MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();
		MathLibrary::Vector2 targetVelocity = m_target->getTransform()->getVelocity();

		MathLibrary::Vector2 targetPoint = targetPosition + targetVelocity;

		//Display what it is running from
		DrawLine(targetPoint.x, targetPoint.y, ownerPosition.x, ownerPosition.y, RED);

		//Calculates a vector from the owner to the targets postion + their velocity (targetPoint), then normalizes it
		MathLibrary::Vector2 distanceVector = targetPoint - ownerPosition;
		distanceVector.normalize();

		//Calculates the desiredVelocity (Max velocity is positive to make the Agent Pursue)
		MathLibrary::Vector2 desiredVelocity = distanceVector * getOwner()->getTransform()->getMaxVelocity();
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

