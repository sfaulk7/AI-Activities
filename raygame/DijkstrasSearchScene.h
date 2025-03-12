#pragma once
#include "Scene.h"
#include "Pathfinding/DijkstrasNodeMap.h"
#include "Pathfinding/DijkstrasPathAgent.h"

class DijkstrasSearchScene :
    public Scene
{
public:
    void start() override;
    void update(float deltaTime) override;
    void end() override;

private:
    pathfinding::NodeMap m_nodeMap;
    pathfinding::PathAgent* m_pathAgent;

};