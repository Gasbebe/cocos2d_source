#ifndef __STAGE1_SCENE_H__
#include "cocos2d.h"
#include "HelloWorldScene.h"

class Stage1 : public cocos2d::LayerColor {

public:
	enum PlayerState
	{
		SWORD, HOLY, KEY, ROAD, IDLE
	};
	PlayerState ps = IDLE;
	int count = 0;
	//void createHero();
	cocos2d::Size winSize;
	cocos2d::Vec2 HeroPosition;
	cocos2d::Sprite* Hero;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* items;
	cocos2d::TMXLayer* metainfo;
	HelloWorld* hello;
	//virtual void onEnter();
	//virtual void onExit();
	//virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	//void setViewpointCenter(cocos2d::Vec2 position);
	//cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	//void setPlayerPosition(cocos2d::Vec2 position);

	//void StageCheck();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Stage1);
};

#define __STAGE1_SCENE_H__
#endif
