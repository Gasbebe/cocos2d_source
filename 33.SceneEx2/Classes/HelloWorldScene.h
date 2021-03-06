﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	void doChangeScene(Ref* pSender);

	void onEnter();
	//void onEnterTransition();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();
	void onExit();
	~HelloWorld(void);
};

#endif // __HELLOWORLD_SCENE_H__
