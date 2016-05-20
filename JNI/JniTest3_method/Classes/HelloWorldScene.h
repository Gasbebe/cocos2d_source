#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void addSprite(cocos2d::Ref* pSender);
	void removeSprite(cocos2d::Ref* pSender);
	void addSpriteFromJava();
	void removeSpriteFromJava();
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
