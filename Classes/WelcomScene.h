#ifndef WelcomScene_h__
#define WelcomScene_h__
#include "cocos2d.h"

using namespace cocos2d;
class WelcomeScene : public Scene
{
public:
	WelcomeScene();
	~WelcomeScene();

	virtual bool init();

	CREATE_FUNC(WelcomeScene);
};


#endif // WelcomScene_h__

