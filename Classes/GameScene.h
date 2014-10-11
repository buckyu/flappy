#ifndef GameScene_h__
#define GameScene_h__

#include "cocos2d.h"

using namespace cocos2d;
class GameScene:public Scene
{
public:
	GameScene();
	~GameScene();

	virtual bool init();

	CREATE_FUNC(GameScene);
};
#endif // GameScene_h__

