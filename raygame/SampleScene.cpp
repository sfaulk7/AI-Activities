#include "SampleScene.h"
#include "SpriteComponent.h"
#include "SeekComponent.h"
#include "Transform2D.h"

void SampleScene::start()
{
	//This is a better comment
	Actor* player = new Actor(50, 50, "Player");
	player->addComponent(new SpriteComponent(player, "Images/player.png"));
	player->getTransform()->setScale({ 50, 50 });

	Actor* bullet = new Actor(100, 50, "Bullet");
	bullet->addComponent(new SpriteComponent(bullet, "Images/bullet.png"));
	bullet->getTransform()->setScale({ 50, 50 });

	Agent* test3 = new Agent(200, 500, "Enemy");
	test3->addComponent(new SpriteComponent(test3, "Images/enemy.png"));
	test3->addComponent(new SeekComponent(test3, player));
	test3->getTransform()->setScale({ 50, 50 });
	test3->getTransform()->rotate(3.14);

	addActor(player);
	addActor(bullet);
	addActor(test3);
}
