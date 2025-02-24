#pragma once
#include "Component.h"

class MousePositionComponent : public Component
{
public:
    MousePositionComponent() {}
    ~MousePositionComponent();

    MousePositionComponent(Actor* owner);

    void update(float deltaTime);
private:
};