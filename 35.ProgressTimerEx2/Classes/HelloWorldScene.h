﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);

	void myTick(float f);
	void SpriteProgressToRabial(float f);

	int nNum;
	cocos2d::ProgressTimer *pt;
};

#endif // __HELLOWORLD_SCENE_H__
