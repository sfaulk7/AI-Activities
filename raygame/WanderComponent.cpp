#include "WanderComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"
#include "random"

WanderComponent::~WanderComponent()
{
	SetDisabled();
}

WanderComponent::WanderComponent(Actor* owner) : Component(owner, "WanderComponent")
{
	this->SetDisabled();
}

void WanderComponent::update(float deltaTime)
{
	if (GetEnabled() == true)
	{
		DrawText("CurrentBehavior: Wander (2)", 100, 40, 40, YELLOW);

		//Puts the positions and the owner's velocity into variables for ease of use
		MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getLocalPosition();
		MathLibrary::Vector2 ownerVelocity = getOwner()->getTransform()->getVelocity();

		int scale = 200;
		int x = GetRandomValue(-1, 1);
		int y = GetRandomValue(-1, 1);
		x = x * scale;
		y = y * scale;
		//MathLibrary::Vector2 wanderCircle = { x, y };
		MathLibrary::Vector2 wanderPosition = { x + ownerPosition.x, y + ownerPosition.y };

		//Display what it is wandering to
		DrawLine(wanderPosition.x, wanderPosition.y, ownerPosition.x, ownerPosition.y, RED);

		////Calculates a vector from the owner to the target, then normalizes it
		//MathLibrary::Vector2 distanceVector = targetPosition - ownerPosition;
		//float distance = distanceVector.getMagnitude();
		//distanceVector.normalize();


		////Calculates the desiredVelocity
		//MathLibrary::Vector2 desiredVelocity;
		//DrawCircleLines(targetPosition.x, targetPosition.y, 1500, YELLOW);
		//if (distance < 1500)
		//{
		//	desiredVelocity = distanceVector * getOwner()->getTransform()->getMaxVelocity() * (distance / 1500);
		//}
		//else
		//{
		//	desiredVelocity = distanceVector * getOwner()->getTransform()->getMaxVelocity();
		//}


		////Calculates the Steering force
		//MathLibrary::Vector2 steeringForce = desiredVelocity - ownerVelocity;

		////Sets the new velocity
		//getOwner()->getTransform()->setVelocity(ownerVelocity + (steeringForce * deltaTime));

		////Sets the new position
		//getOwner()->getTransform()->setLocalPosition(ownerPosition + (ownerVelocity * deltaTime));

		////Sets the new rotation
		//getOwner()->getTransform()->setRotation(atan2(ownerVelocity.x, ownerVelocity.y));
		//getOwner()->getTransform()->rotate(-1.57);

	}
}

