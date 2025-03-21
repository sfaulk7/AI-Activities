#include "Transform2D.h"
#include "DecisionTreeScene.h"
#include "SpriteComponent.h"
#include "BehaviourComponent.h"
#include "MousePositionComponent.h"
#include "SeekComponent.h"
#include "FleeComponent.h"
#include "WanderComponent.h"
#include "PursueComponent.h"
#include "EvadeComponent.h"
#include "ArriveComponent.h"
#include "DecisionTreeComponent.h"
#include "raylib.h"

/// <summary>
/// The goal is to get it to chase after the target if it isnt a predator and flee if it is 
/// but wander if the target is too far away
/// </summary>
void DecisionTreeScene::start()
{
	Mouse = new Actor(100, 100, "Mouse"); //Target 0
	Mouse->addComponent(new SpriteComponent(Mouse, "Images/bullet.png"));
	Mouse->addComponent(new MousePositionComponent(Mouse));
	Mouse->getTransform()->setScale({ 50, 50 });

	Target1 = new Actor(300, 150, "Target1"); //Target 1
	Target1->addComponent(new SpriteComponent(Target1, "Images/bullet.png"));
	Target1->getTransform()->setScale({ 50, 50 });

	Target2 = new Actor(1100, 150, "Target2"); //Target 2
	Target2->addComponent(new SpriteComponent(Target2, "Images/bullet.png"));
	Target2->getTransform()->setScale({ 50, 50 });

	Target3 = new Actor(700, 500, "Target3"); //Target 3
	Target3->addComponent(new SpriteComponent(Target3, "Images/bullet.png"));
	Target3->getTransform()->setScale({ 50, 50 });

	Target4 = new Actor(300, 850, "Target4"); //Target 4
	Target4->addComponent(new SpriteComponent(Target4, "Images/bullet.png"));
	Target4->getTransform()->setScale({ 50, 50 });

	Target5 = new Actor(1100, 850, "Target5"); //Target 5
	Target5->addComponent(new SpriteComponent(Target5, "Images/bullet.png"));
	Target5->getTransform()->setScale({ 50, 50 });

	Enemy = new Agent(200, 500, "Enemy");
	Enemy->getTransform()->setMaxVelocity(500);
	Enemy->addComponent(new WanderComponent(Enemy)); //Behavior 0
	Enemy->addComponent(new SeekComponent(Enemy, Mouse)); //Behavior 1
	Enemy->addComponent(new FleeComponent(Enemy, Mouse)); //Behavior 2
	Enemy->addComponent(new SpriteComponent(Enemy, "Images/Enemy.png"));
	Enemy->addComponent(new DecisionTreeComponent(Enemy, Mouse));
	Enemy->getTransform()->setScale({ 50, 50 });
	Enemy->EnableBehavior(4);

	addActor(Mouse);
	addActor(Target1);
	addActor(Target2);
	addActor(Target3);
	addActor(Target4);
	addActor(Target5);
	addActor(Enemy);

	DecisionTreeComponent* Tree = Enemy->getComponent<DecisionTreeComponent>();
	Tree->AddAnotherTarget(Target1);
	Tree->AddAnotherTarget(Target2);
	Tree->AddAnotherTarget(Target3);
	Tree->AddAnotherTarget(Target4);
	Tree->AddAnotherTarget(Target5);

}

void DecisionTreeScene::update(float deltaTime)
{
	Scene::update(deltaTime);

	DecisionTreeComponent* Tree = Enemy->getComponent<DecisionTreeComponent>();
	Tree->AddAnotherTarget(Target1);
	Tree->AddAnotherTarget(Target2);
	Tree->AddAnotherTarget(Target3);
	Tree->AddAnotherTarget(Target4);
	Tree->AddAnotherTarget(Target5);

	SeekComponent* Seek = Enemy->getComponent<SeekComponent>();
	FleeComponent* Flee = Enemy->getComponent<FleeComponent>();

	Seek->ChangeTarget(Tree->CurrentTarget());
	Flee->ChangeTarget(Tree->CurrentTarget());
}
