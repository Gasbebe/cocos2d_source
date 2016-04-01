#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
	enum PlayerState
	{
		SWORD, HOLY, KEY, ROAD, IDLE
	};
	PlayerState ps = IDLE;
	bool bClear = false;
	int stage = 1;
	void createHero();
	cocos2d::Size winSize;

	cocos2d::Vec2 HeroPosition;
	cocos2d::Vec2 MonsterPosition;
	cocos2d::Vec2 DemonPosition;

	cocos2d::Sprite* Hero;
	cocos2d::Sprite* Monster;
	cocos2d::Sprite* Demon;

	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* items;
	cocos2d::TMXLayer* metainfo;
	cocos2d::TMXObjectGroup* monsterSpawn;
	cocos2d::TMXObjectGroup* objects;

	cocos2d::SpriteFrameCache* cache;

	virtual void onEnter();//화면이나올떄
	virtual void onExit();//화면이 사라질때
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void setViewpointCenter(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);
	void createMonster(cocos2d::Vec2 spawn);
	void createDemon(cocos2d::Vec2 spawn);
	void StageCheck(float t);
};

#endif // __HELLOWORLD_SCENE_H__
