﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	//cocos2d::TMXTiledMap* map;
	cocos2d::Sprite* m_tamara;
    CREATE_FUNC(HelloWorld);
	void repositionSprite(float t);
};

#endif // __HELLOWORLD_SCENE_H__
