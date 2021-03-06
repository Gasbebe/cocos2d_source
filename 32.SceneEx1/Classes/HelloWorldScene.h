﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);

	cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);
	void doPushScene(Ref* pSender);
	void doPushSceneTran(Ref* pSender);
	void doReplaceScene(Ref* pSender);
	void doReplaceSceneTran(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
