#include "GameLayer.h"
#include "Utils/AtlasLoader.h"
#include "BackgroundLayer.h"

using namespace std;

GameLayer::GameLayer()
{
}


GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	if (Layer::init())
	{

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		this->gameStatus = GAME_STATE_READY;

		this->score = 0;

		//add brid 
		this->brid = BridSprite::getInstance();
		this->brid->createBrid();

		PhysicsBody *body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(false);
		body->setContactTestBitmask(1);

		this->brid->setPhysicsBody(body);
		this->brid->setPosition(origin.x + visibleSize.width * 1 / 3 - 5, origin.y + visibleSize.height / 2 + 5);
		this->brid->idle();
		this->addChild(brid);


		// Add the ground
		this->groundNode = Node::create();
		float landHeight = BackgroundLayer::getLandHeight();
		auto groundBody = PhysicsBody::create();
		groundBody->addShape(PhysicsShapeBox::create(Size(288, landHeight)));
		groundBody->setDynamic(false);
		groundBody->setLinearDamping(0.0f);
		groundBody->setContactTestBitmask(1);

		this->groundNode->setPhysicsBody(groundBody);
		this->groundNode->setPosition(144, landHeight / 2);
		this->addChild(this->groundNode);



		Sprite *pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		Sprite *pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
		Node* siglePip = Node::create();
		siglePip->addChild(pipDown, 0, DOWN_PIP);
		siglePip->addChild(pipUp, 0, UP_PIP);
		//siglePip->setPosition(visibleSize.width + i )
		//siglePip->setPosition(visibleSize.width + i*PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());


		shiftLand = schedule_selector(GameLayer::scrollLand);
		this->schedule(shiftLand, 0.01f);


		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = 
			CC_CALLBACK_1(GameLayer::onContactBegin, this);
		this->getEventDispatcher()->addEventListenerWithFixedPriority(contactListener, -128);





		//auto dispatcher = Director::getInstance()->getEventDispatcher();
		////auto listener = EventListenerTouchOneByOne::create();
		////listener->onTouchBegan = [](Touch*, Event*)->bool{
		////	return false;
		////};/*CC_CALLBACK_2(GameLayer::onTouchesBegan, this);*/
		////dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		//auto multiListener = EventListenerTouchAllAtOnce::create();
		//multiListener->onTouchesBegan = [](const std::vector<Touch*>, Event*)->void{
		//	int brk = 0;
		//	return;
		//};/*CC_CALLBACK_2(GameLayer::onTouchesBegan, this);*/
		//dispatcher->addEventListenerWithSceneGraphPriority(multiListener, this);
		// dispatcher->addEventListenerWithFixedPriority(listener, -128);
// 		dispatcher->addEventListenerWithFixedPriority
// 
		this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
		this->setTouchEnabled(true);

		return true;
	}
	else
	{
		return false;
	}
}

bool GameLayer::onContactBegin( PhysicsContact& contact) {

	this->gameOver();
	return true;
}


void GameLayer::gameOver()
{
	if (this->gameStatus == GAME_STATE_OVER) {
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
	//get the best score
	//int bestScore = UserRecord::getInstance()->readIntegerFromUserDefault("best_score");
	//update the best score
// 	if (this->score > bestScore){
// 		UserRecord::getInstance()->saveIntegerToUserDefault("best_score", this->score);
// 	}
	//this->delegator->onGameEnd(this->score, bestScore);
	this->unschedule(shiftLand);
	SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
	this->brid->die();
	this->brid->setRotation(-90);
	//this->birdSpriteFadeOut();

	FadeOut* animation = FadeOut::create(1.5);
	CallFunc* animationDone = CallFunc::create(bind(&GameLayer::birdSpriteRemove, this));
	Sequence* sequence = Sequence::createWithTwoActions(animation, animationDone);
	this->brid->stopAllActions();
	this->brid->runAction(sequence);

	this->gameStatus = GAME_STATE_OVER;
}


void GameLayer::birdSpriteRemove(){
	this->brid->setRotation(0);
	this->removeChild(this->brid);
}

void  GameLayer::onTouch()
{
	if (this->gameStatus == GAME_STATE_OVER) {
		return ;
	}

	SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if (this->gameStatus == GAME_STATE_READY) {
		//this->delegator->onGameStart();
		this->brid->fly();
		this->gameStatus = GAME_STATE_START;
		this->createPips();
	}
	else if (this->gameStatus == GAME_STATE_START) {
		this->brid->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
	return ;
}

void GameLayer::scrollLand(float dt)
{


	// move the pips
	for(auto singlePip : pips) {
		singlePip->setPositionX(singlePip->getPositionX() - 2);
		if (singlePip->getPositionX() < -PIP_WIDTH) {
			singlePip->setTag(PIP_NEW);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			singlePip->setPositionX(visibleSize.width);
			singlePip->setPositionY(this->getRandomHeight());
		}
	}
}

void GameLayer::createPips()
{
	// Create the pips
	for (int i = 0; i < PIP_COUNT; i++) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Sprite *pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		Sprite *pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
		Node *singlePip = Node::create();

		// bind to pair
		pipDown->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
		singlePip->addChild(pipDown, 0, DOWN_PIP);
		singlePip->addChild(pipUp, 0, UP_PIP);
		singlePip->setPosition(visibleSize.width + i*PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());
		auto body = PhysicsBody::create();
		auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIP_HEIGHT + PIP_DISTANCE));
		body->addShape(shapeBoxDown);
		body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));
		body->setDynamic(false);
		body->setContactTestBitmask(1);

		singlePip->setPhysicsBody(body);
		singlePip->setTag(PIP_NEW);

		this->addChild(singlePip);
		pips.push_back(singlePip);
	}
}

float GameLayer::getRandomHeight()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return rand() % (int)(2 * PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}

void GameLayer::update(float delta)
{
	if (this->gameStatus == GAME_STATE_START)
	{
		this->rotateBird();
		this->checkHit();
	}

}

void GameLayer::rotateBird() {
	float verticalSpeed = this->brid->getPhysicsBody()->getVelocity().y;
	this->brid->setRotation(min(max((double)-90, (verticalSpeed*0.2 + 60)), (double)30));
}

void GameLayer::checkHit() {
	for each (auto pip in this->pips) {
		if (pip->getTag() == PIP_NEW) {
			if (pip->getPositionX() < this->brid->getPositionX()) {
				SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
				this->score++;
				//this->delegator->onGamePlaying(this->score);
				pip->setTag(PIP_PASS);
			}
		}
	}
}

void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	//int brk = 3;
	this->onTouch();
}
