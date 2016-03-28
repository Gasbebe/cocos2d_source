#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	cocos2d::Sprite* pMan;

	virtual void onEnter();
	virtual void onExit();
	virtual void onTouchBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	virtual void onTouchCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
