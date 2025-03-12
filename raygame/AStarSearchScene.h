#pragma once
#include "Scene.h"
#include "Pathfinding/AStarNodeMap.h"
#include "Pathfinding/AStarPathAgent.h"

class AStarSearchScene :
    public Scene
{
public:
    void start() override;
    void update(float deltaTime) override;
    void end() override;

private:
    AStarpathfinding::NodeMap m_nodeMap;
    AStarpathfinding::PathAgent* m_pathAgent;

};