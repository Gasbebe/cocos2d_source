﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchMove(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void showParticle(cocos2d::Vec2 point);
};

#endif // __HELLOWORLD_SCENE_H__
