#include "Agent.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"

Agent::Agent()
{
    m_transform = new Transform2D(this);
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

void Agent::SetBehavior(int behavior)
{

}
