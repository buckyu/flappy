#ifndef BridSprite_h__
#define BridSprite_h__

#include "cocos2d.h"

using namespace cocos2d;


typedef enum 
{
	ACTION_STATE_IDLE,
	ACTION_STATE_FLY,
	ACTION_STATE_DIE
} ActionState;

const int BIRD_SPRITE_TAG = 10003;

class BridSprite:public Sprite
{
public:
	BridSprite();
	~BridSprite();

	static BridSprite* getInstance();

	virtual bool init();

	bool createBrid();

	void idle();

	void fly();

	void die();

protected:
	static cocos2d::Animation *createAnimation(const char *fmt, int count, float fps);

	void createBirdByRandom();

private:

	bool changeState(ActionState state);

	static BridSprite* _instance;

	std::string bridName;

	std::string birdNameFormat;

	Action* idleAction;

	//Action* flyAction;

	Action* swingAction;

	ActionState currentState;
};
#endif // BridSprite_h__

