﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);


	void onEnter();
	void onExit();
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
	cocos2d::Sprite* pMan;
	bool bSelect;
	float gRotation;
};

#endif // __HELLOWORLD_SCENE_H__