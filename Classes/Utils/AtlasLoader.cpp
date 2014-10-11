
#include "AtlasLoader.h"
#include "cocos2d/cocos/renderer/CCTexture2D.h"


AtlasLoader* AtlasLoader::_instance = NULL;
AtlasLoader::AtlasLoader()
{
}


AtlasLoader::~AtlasLoader()
{
}

AtlasLoader* AtlasLoader::getInstance()
{
	if (NULL == _instance)
		_instance = new AtlasLoader();
	return _instance;
}

void AtlasLoader::destoryInstance()
{
	CC_SAFE_DELETE(_instance);
}

void AtlasLoader::loadAtlas(std::string filename)
{
	cocos2d::Texture2D* texture = cocos2d::Director::getInstance()->getTextureCache()->addImage("atlas");
	loadAtlas(filename, texture);
}

void AtlasLoader::loadAtlas(std::string filename, cocos2d::Texture2D* texture)
{
	std::string data = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
	unsigned pos;
	Atlas atlas;
	pos = data.find_first_of("\n");
	std::string line = data.substr(0, pos);
	data = data.substr(pos + 1);
	while (line != ""){
		sscanf(line.c_str(), "%s %d %d %f %f %f %f",
			atlas.name, &atlas.width, &atlas.height, &atlas.start.x,
			&atlas.start.y, &atlas.end.x, &atlas.end.y);
		atlas.start.x = 1024 * atlas.start.x;
		atlas.start.y = 1024 * atlas.start.y;
		atlas.end.x = 1024 * atlas.end.x;
		atlas.end.y = 1024 * atlas.end.y;
		pos = data.find_first_of("\n");
		line = data.substr(0, pos);
		data = data.substr(pos + 1);
		cocos2d::Rect rect = cocos2d::Rect(atlas.start.x, atlas.start.y, atlas.width, atlas.height);
		cocos2d::SpriteFrame* frame = cocos2d::SpriteFrame::createWithTexture(texture, rect);
		this->_spriteFrames.insert((atlas.name), frame);
	}
}

cocos2d::SpriteFrame* AtlasLoader::getSpriteFrameByName(std::string name)
{
	return this->_spriteFrames.at(name);
}



