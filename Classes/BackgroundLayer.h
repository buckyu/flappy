#ifndef BackgroundLayer_h__
#define BackgroundLayer_h__

#include "cocos2d.h"
using namespace cocos2d;
class BackgroundLayer : public Layer
{
public:
	BackgroundLayer();
	~BackgroundLayer();

	virtual bool init();
	
	CREATE_FUNC(BackgroundLayer);

	static float getLandHeight();

};

#endif // BackgroundLayer_h__

