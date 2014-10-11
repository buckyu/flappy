#include "GameScene.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

bool GameScene::init()
{

	if (Scene::initWithPhysics())
	{

		this->getPhysicsWorld()->setGravity(Vect(0, -900));

		auto backgroud = BackgroundLayer::create();
		if (backgroud)
		{
			this->addChild(backgroud);
		}

		auto gameLayer = GameLayer::create();
		if (gameLayer)
		{
			gameLayer->setPhyWorld(this->getPhysicsWorld());
			this->addChild(gameLayer);
		}
// 
// 		auto oLayer = OptionLayer::create();
// 		if (oLayer)
// 		{
// 			oLayer->setDelegator(gameLayer);
// 			this->addChild(oLayer);
// 
// 		}


		return true;
	}
	else
	{
		return true;
	}


}
