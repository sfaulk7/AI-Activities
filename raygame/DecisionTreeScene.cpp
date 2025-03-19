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

void DecisionTreeScene::start()
{
	fill = new Actor(100, 100, "fill");

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
	Enemy->addComponent(new SeekComponent(Enemy, fill)); //Behavior 1
	Enemy->addComponent(new FleeComponent(Enemy, fill)); //Behavior 2
	Enemy->addComponent(new SpriteComponent(Enemy, "Images/Enemy.png"));
	Enemy->addComponent(new DecisionTreeComponent(Enemy, fill));
	Enemy->getTransform()->setScale({ 50, 50 });
	Enemy->EnableBehavior(4);

	addActor(Mouse);
	addActor(Target1);
	addActor(Target2);
	addActor(Target3);
	addActor(Target4);
	addActor(Target5);
	addActor(Enemy);
}

void DecisionTreeScene::update(float deltaTime)
{
	Scene::update(deltaTime);

	if (IsKeyPressed(KEY_ZERO))
	{
		fill = Mouse;
	}
	if (IsKeyPressed(KEY_ONE))
	{
		fill = Target1;
	}
	if (IsKeyPressed(KEY_TWO))
	{
		fill = Target2;
	}
	if (IsKeyPressed(KEY_THREE))
	{
		fill = Target3;
	}
	if (IsKeyPressed(KEY_FOUR))
	{
		fill = Target4;
	}
	if (IsKeyPressed(KEY_FIVE))
	{
		fill = Target5;
	}

	switch (GetKeyPressed())
	{
	KEY_ZERO:
		fill = Mouse;
		break;
	KEY_ONE:
		fill = Target1;
		break;
	KEY_TWO:
		fill = Target2;
		break;
	KEY_THREE:
		fill = Target3;
		break;
	KEY_FOUR:
		fill = Target4;
		break;
	KEY_FIVE:
		fill = Target5;
		break;
	}
}
