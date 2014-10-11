#ifndef LoadingScene_h__
#define LoadingScene_h__

#include "cocos2d.h"

using namespace cocos2d;

using namespace CocosDenshion;

class LoadingScene : public Scene
{
public:
	LoadingScene();
	~LoadingScene();

	virtual bool init();

	CREATE_FUNC(LoadingScene);

	void onEnter() override;

private: 

	void loadingCallBack(Texture2D* texture);
};

#endif // LoadingScene_h__

