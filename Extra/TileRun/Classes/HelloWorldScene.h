#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(HelloWorld);

	void createPlayer();
	cocos2d::Size winSize;
	cocos2d::Vec2 playerPosition;
	cocos2d::Sprite* player;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* Check;


	void MoveBackgoround(float t);
	void CheckBackground(float t);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);
};

#endif // __HELLOWORLD_SCENE_H__
