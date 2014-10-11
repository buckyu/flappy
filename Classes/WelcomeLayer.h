#ifndef WelcomeLayer_h__
#define WelcomeLayer_h__

#include "cocos2d.h"
using namespace cocos2d;
#include "BridSprite.h"


class WelcomeLayer : public Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();

	virtual bool init();

	CREATE_FUNC(WelcomeLayer);

private:
	/**
	* The start button has been pressed will call this functison
	*/
	void menuStartCallback(Object *sender);

	/**
	* This method is make the land have a scroll animation
	*/
	void scrollLand(float dt);

	Sprite *land1;
	Sprite *land2;
	BridSprite *bird;

};
#endif // WelcomeLayer_h__

