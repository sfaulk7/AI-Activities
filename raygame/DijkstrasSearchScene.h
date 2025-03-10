#pragma once
#include "Scene.h"
class DijkstrasSearchScene :
    public Scene
{
public:
    void start() override;
    void update(float deltaTime) override;
private:
    int testcount;

};