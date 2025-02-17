#include "SampleScene.h"
#include "SpriteComponent.h"
#include "Transform2D.h"

void SampleScene::start()
{
	//This is a better comment
	Actor* test = new Actor(50, 50, "Test");
	test->addComponent(new SpriteComponent(test, "Images/player.png"));
	test->getTransform()->setScale({ 50, 50 });

	Actor* test2 = new Actor(100, 50, "Test2");
	test2->addComponent(new SpriteComponent(test2, "Images/bullet.png"));
	test2->getTransform()->setScale({ 50, 50 });

	Actor* test3 = new Actor(200, 50, "Test3");
	test3->addComponent(new SpriteComponent(test3, "Images/enemy.png"));
	test3->getTransform()->setScale({ 50, 50 });
	test3->getTransform()->rotate(3.14);

	addActor(test);
	addActor(test2);
	addActor(test3);
}
