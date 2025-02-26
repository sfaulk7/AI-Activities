#include "SeekComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"

SeekComponent::~SeekComponent()
{
	SetDisabled();
}

SeekComponent::SeekComponent(Actor* owner, Actor* Target) : Component(owner, "SeekComponent")
{
	m_target = Target;
	this->SetDisabled();
}

void SeekComponent::update(float deltaTime)
{
	if (GetEnabled() == true)
	{
		//DrawText("CurrentBehavior: Seek (0)", 100, 40, 40, YELLOW);

		//Puts the positions and the owner's velocity into variables for ease of use
		MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getLocalPosition();
		MathLibrary::Vector2 ownerVelocity = getOwner()->getTransform()->getVelocity();
		MathLibrary::Vector2 targetPosition = m_target->getTransform()->getLocalPosition();

		//Display what it is chasing
		DrawLine(targetPosition.x, targetPosition.y, ownerPosition.x, ownerPosition.y, RED);

		//Calculates a vector from the owner to the target, then normalizes it
		MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
		distanceVector.normalize();

		//Calculates the desiredVelocity (Max velocity is positive to make the Agent seek)
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

