#include "Transform2D.h"
#include "FiniteStateMachineScene.h"
#include "SpriteComponent.h"
#include "BehaviourComponent.h"
#include "MousePositionComponent.h"
#include "SeekComponent.h"
#include "FleeComponent.h"
#include "WanderComponent.h"
#include "PursueComponent.h"
#include "EvadeComponent.h"
#include "ArriveComponent.h"
#include "FiniteStateMachine.h"

void FiniteStateMachineScene::start()
{
	Actor* mouse = new Actor(100, 100, "Mouse");
	mouse->addComponent(new SpriteComponent(mouse, "Images/bullet.png"));
	mouse->addComponent(new MousePositionComponent(mouse));
	mouse->getTransform()->setScale({ 50, 50 });

	Agent* enemy = new Agent(200, 500, "Enemy");
	enemy->getTransform()->setMaxVelocity(500);
	enemy->addComponent(new SeekComponent(enemy, mouse)); //Behavior 0
	enemy->addComponent(new FleeComponent(enemy, mouse)); //Behavior 1
	enemy->addComponent(new WanderComponent(enemy)); //Behavior 2
	enemy->addComponent(new PursueComponent(enemy, mouse)); //Behavior 3
	enemy->addComponent(new EvadeComponent(enemy, mouse)); //Behavior 4
	enemy->addComponent(new ArriveComponent(enemy, mouse)); //Behavior 5

	//enemy->addComponent(new BehaviourComponent(enemy));
	enemy->addComponent(new SpriteComponent(enemy, "Images/enemy.png"));
	enemy->addComponent(new FiniteStateMachine(enemy, mouse));

	enemy->getTransform()->setScale({ 50, 50 });

	enemy->EnableTag(); 

	addActor(mouse);
	addActor(enemy);
}
