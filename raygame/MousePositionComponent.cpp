#include "MousePositionComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "math.h"
#include "raylib.h"

MousePositionComponent::~MousePositionComponent()
{
	SetDisabled();
}

MousePositionComponent::MousePositionComponent(Actor* owner) : Component(owner, "MousePositionComponent")
{
	this->SetEnabled();
}

void MousePositionComponent::update(float deltaTime)
{
	if (this->GetEnabled() == true)
	{
		//Makes raylibs mouse postion into a MathLibrary::Vector2
		MathLibrary::Vector2 mousePosition(GetMousePosition().x, GetMousePosition().y);

		getOwner()->getTransform()->setLocalPosition(mousePosition);

	}
}

