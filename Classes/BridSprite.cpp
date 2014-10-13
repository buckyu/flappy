#include "BridSprite.h"

#include "Utils/AtlasLoader.h"

BridSprite* BridSprite::_instance = NULL;

BridSprite::BridSprite()
{
}

BridSprite::~BridSprite()
{
}

BridSprite* BridSprite::getInstance()
{
	if (_instance == NULL){
		_instance = new BridSprite();
		if (!_instance->init()){
			delete(_instance);
			_instance = NULL;
			CCLOG("ERROR: Could not init shareBirdSprite");
		}
	}
	return _instance;
}

bool BridSprite::init()
{
	return true;
}

bool BridSprite::createBrid()
{
	this->createBirdByRandom();
	if (Sprite::initWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(this->bridName)))
	{
		// init idle status
		//create the bird animation
		Animation* animation = this->createAnimation(this->birdNameFormat.c_str(), 3, 10);
		Animate* animate = Animate::create(animation);
		this->idleAction = RepeatForever::create(animate);

		// create the swing action
		ActionInterval *up = CCMoveBy::create(0.4f, Point(0, 12));
		ActionInterval *upBack = up->reverse();
		this->swingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));
		return true;
	}
	else
	{
		return false;
	}
}

void BridSprite::createBirdByRandom()
{
// 	if (this->isFirstTime & 1){
// 		this->isFirstTime &= 2;
// 	}
// 	else if (this->isFirstTime & 2){
// 		this->isFirstTime &= 1;
// 		return;
// 	}
	srand((unsigned)time(NULL));
	int type = ((int)rand()) % 3;
	switch (type)
	{
	case 0:
		this->bridName = "bird0_0";
		this->birdNameFormat = "bird0_%d";
		break;
	case 1:
		this->bridName = "bird1_0";
		this->birdNameFormat = "bird1_%d";
		break;
	case 2:
		this->bridName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	default:
		this->bridName = "bird2_0";
		this->birdNameFormat = "bird2_%d";
		break;
	}
}

Animation* BridSprite::createAnimation(const char *fmt, int count, float fps) {
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(1 / fps);
	for (int i = 0; i < count; i++){
		const char *filename = String::createWithFormat(fmt, i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

void BridSprite::idle()
{
	if (changeState(ACTION_STATE_IDLE)) {
		this->runAction(idleAction);
		this->runAction(swingAction);
	}
}

void BridSprite::fly()
{
	if (changeState(ACTION_STATE_FLY)) {
		this->stopAction(swingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}
}

void BridSprite::die()
{
	if (changeState(ACTION_STATE_DIE)) {
		this->stopAllActions();
	}
}

bool BridSprite::changeState(ActionState state)
{
	currentState = state;
	return true;
}
