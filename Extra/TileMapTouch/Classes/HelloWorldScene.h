#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	cocos2d::TMXTiledMap* map;
	void onEnter();
	void onExit();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Vec2 touchToXY(cocos2d::Vec2 touch, int mapsize);
};

#endif // __HELLOWORLD_SCENE_H__
