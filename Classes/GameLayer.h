#ifndef GameLayer_h__
#define GameLayer_h__

#include "cocos2d.h"
#include "BridSprite.h"
#include "OptionLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

const int UP_PIP = 21;

const int DOWN_PIP = 12;

const int PIP_PASS = 30;

const int PIP_NEW = 31;

/**
* The radius of the bird
*/
const int BIRD_RADIUS = 15;

/**
* The height of the pips
*/
const int PIP_HEIGHT = 320;

/**
* The width of the pips
*/
const int PIP_WIDTH = 52;

/**
* Pip shift speed
*/
const float PIP_SHIFT_SPEED = 80.0f;

/**
* The distance between the down pip and up pip
*/
const int PIP_DISTANCE = 100;

/**
* The distance between the pips vertical
*/
const int PIP_INTERVAL = 180;

/**
* The number of pip pairs display in the screen in the same time
*/
const int PIP_COUNT = 2;

/**
* The distance that the pip will display in the screen, for player to ready
*/
const int WAIT_DISTANCE = 100;

class GameLayer : public Layer 
{
	typedef enum _game_status
	{
		GAME_STATE_READY = 1,
		GAME_STATE_START,
		GAME_STATE_OVER
	} GameStatus;


public:
	GameLayer();
	~GameLayer();

	virtual bool init();

    void onTouch();

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) override;

	void update(float delta);

	CREATE_FUNC(GameLayer);
	
	void setPhyWorld(PhysicsWorld* world){ this->world = world; }

private:

	std::vector<Node *> pips;

	float getRandomHeight();
	
	bool onContactBegin( PhysicsContact& contact);
	
	void gameOver();
	
	void createPips();
	
	void rotateBird();
	
	void checkHit();

	void scrollLand(float dt);

	void birdSpriteRemove();

	BridSprite* brid;

	Node *groundNode;

	GameStatus gameStatus;

	int score;

	PhysicsWorld *world;

	SEL_SCHEDULE  shiftLand;
	
};
#endif // GameLayer_h__

