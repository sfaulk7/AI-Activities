#include "Agent.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"

Agent::Agent() : Actor()
{
    Actor::m_transform = new Transform2D(this);
}

Agent::~Agent()
{
    delete m_transform;
}

Agent::Agent(float x, float y, const char* name = "Agent")
{
    //Initialze default values
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_name = name;
    
}

void Agent::EnableBehavior(int behavior)
{
    for (int i = 0; i <= 5; i++)
    {
        if (i >= m_components.Length())
            break;
        if (i == behavior)
            this->m_components[i]->SetEnabled();
    }
}

void Agent::DisableBehavior(int behavior)
{
    for (int i = 0; i <= 5; i++)
    {
        if (i >= m_components.Length())
            break;
        if (i == behavior)
            this->m_components[i]->SetDisabled();
    }
}

void Agent::EnableAllBehaviors()
{
    for (int i = 0; i <= 5; i++)
    {
        if (i >= m_components.Length())
            break;

        this->m_components[i]->SetEnabled();
    }
}

void Agent::DisableAllBehaviors()
{
    for (int i = 0; i <= 5; i++)
    {
        if (i >= m_components.Length())
            break;

        this->m_components[i]->SetDisabled();
    }
}

bool Agent::GetBehaviorStatus(int behavior)
{
    for (int i = 0; i <= 5; i++)
    {
        if (i >= m_components.Length())
            break;
        if (i == behavior)
            return this->m_components[i]->GetEnabled();
    }

    return false;
}

void Agent::EnableTag()
{
    for (int i = 0; i <= m_components.Length(); i++)
    {
        if (i >= m_components.Length())
            break;
        if (i == m_components.Length() - 1)
            this->m_components[i]->SetEnabled();
    }
}

void Agent::DisableTag()
{
    for (int i = 0; i <= m_components.Length(); i++)
    {
        if (i >= m_components.Length())
            break;
        if (i == m_components.Length() - 1)
            this->m_components[i]->SetDisabled();
    }
}

