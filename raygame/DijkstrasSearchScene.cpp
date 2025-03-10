#include "DijkstrasSearchScene.h"
#include "Pathfinding.h"
#include "NodeMap.h"

void DijkstrasSearchScene::start()
{


	//Actor* mouse = new Actor(100, 100, "Mouse");
	//mouse->addComponent(new SpriteComponent(mouse, "Images/bullet.png"));
	//mouse->addComponent(new MousePositionComponent(mouse));
	//mouse->getTransform()->setScale({ 50, 50 });

	//Agent* enemy = new Agent(200, 500, "Enemy");
	//enemy->getTransform()->setMaxVelocity(500);
	//enemy->addComponent(new SeekComponent(enemy, mouse)); //Behavior 0
	//enemy->addComponent(new FleeComponent(enemy, mouse)); //Behavior 1
	//enemy->addComponent(new WanderComponent(enemy)); //Behavior 2
	//enemy->addComponent(new PursueComponent(enemy, mouse)); //Behavior 3
	//enemy->addComponent(new EvadeComponent(enemy, mouse)); //Behavior 4
	//enemy->addComponent(new ArriveComponent(enemy, mouse)); //Behavior 5

	////enemy->addComponent(new BehaviourComponent(enemy));
	//enemy->addComponent(new SpriteComponent(enemy, "Images/enemy.png"));
	//enemy->addComponent(new FiniteStateMachine(enemy, mouse));

	//enemy->getTransform()->setScale({ 50, 50 });

	//enemy->EnableTag();

	//addActor(mouse);
	//addActor(enemy);
	testcount = 0;
}

void DijkstrasSearchScene::update(float deltaTime)
{
	//Pathfinding::Node a(GetRandomValue(50, 1350), GetRandomValue(50, 950));
	//Pathfinding::Node b(GetRandomValue(50, 1350), GetRandomValue(50, 950));
	//Pathfinding::Node c(GetRandomValue(50, 1350), GetRandomValue(50, 950));

	Pathfinding::Node a(150, 250);
	Pathfinding::Node b(450, 550);
	Pathfinding::Node c(50, 450);

	a.ConnectTo(&b, 7);
	a.ConnectTo(&c, 3);

	List<Pathfinding::Node*> list;
	Pathfinding::DrawGraph(&a, &list);

	List<Pathfinding::Node*> path = { &a, &b, &c };
	Pathfinding::DrawPath(path, WHITE);

	Pathfinding::DrawNode(&a, false);
	Pathfinding::DrawNode(&b, true);
	Pathfinding::DrawNode(&c, false);

	//Pathfinding::DijkstrasSearch(&a, &c);

}
