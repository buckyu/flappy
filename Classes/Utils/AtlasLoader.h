#ifndef AtlasLoader_h__
#define AtlasLoader_h__

#include "cocos2d.h"

typedef struct _atias
{
	char name[255];
	int width;
	int height;
	cocos2d::Point start;
	cocos2d::Point end;
} Atlas;

class AtlasLoader
{
public:
	AtlasLoader();
	~AtlasLoader();

	static AtlasLoader* getInstance();

	static void destoryInstance();

	void loadAtlas(std::string filename);
	void loadAtlas(std::string filename, cocos2d::Texture2D* texture);

	cocos2d::SpriteFrame* getSpriteFrameByName(std::string name);
private:
	cocos2d::Map< std::string, cocos2d::SpriteFrame* > _spriteFrames;

	static AtlasLoader *_instance;
	
};
#endif // AtlasLoader_h__
