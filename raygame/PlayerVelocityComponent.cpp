#include "PlayerVelocityComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"

PlayerVelocityComponent::~PlayerVelocityComponent()
{
	SetDisabled();
}

PlayerVelocityComponent::PlayerVelocityComponent(Actor* owner) : Component(owner, "PlayerVelocityComponent")
{
	this->SetDisabled();
}

void PlayerVelocityComponent::update(float deltaTime)
{
	if (this->GetEnabled() == true);
	{
		//Puts the positions and the owner's velocity into variables for ease of use
		MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getLocalPosition();
		MathLibrary::Vector2 ownerVelocity = getOwner()->getTransform()->getVelocity();
		MathLibrary::Vector2 previousPosition = ownerPosition;

		//Movement
		if (IsKeyDown(KEY_A))

		//Calculates a vector from the owner to the target, then normalizes it
		MathLibrary::Vector2 distanceVector = ownerPosition - previousPosition;
		distanceVector.normalize();

		//Calculates the desiredVelocity (Max velocity is positive to make the Agent PlayerVelocity)
		MathLibrary::Vector2 desiredVelocity = distanceVector * getOwner()->getTransform()->getMaxVelocity();
		//Calculates the Steering force
		MathLibrary::Vector2 SteeringForce = desiredVelocity - ownerVelocity;

		//Sets the new velocity
		getOwner()->getTransform()->setVelocity(ownerVelocity + (SteeringForce * deltaTime));

		//Sets the new position
		getOwner()->getTransform()->setLocalPosition(ownerPosition + (ownerVelocity * deltaTime));

		//Sets the new rotation
		getOwner()->getTransform()->setRotation(atan2(ownerVelocity.x, ownerVelocity.y));
		getOwner()->getTransform()->rotate(-1.57);

		
	}
}

