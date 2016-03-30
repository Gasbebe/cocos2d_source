#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);

	cocos2d::Sprite* bubble;
	cocos2d::Sprite* bubble2;
	cocos2d::Sprite* bubble3;
	cocos2d::Sprite* bubble4;
	cocos2d::Sprite* bubbleStar;
	cocos2d::Sprite* bubbleStar2;
	cocos2d::Sprite* bubbleStar3;

	cocos2d::Sprite* logo;
	cocos2d::Sprite* buttonFx;
	cocos2d::Sprite* buttonStart;
	cocos2d::Sprite* buttonInfo;
	cocos2d::Sprite* buttonEx;
	cocos2d::Sprite* buttonExBase;

	cocos2d::Sprite* topLite;
	cocos2d::Sprite* leftLite;
	cocos2d::Sprite* bgLite;
	cocos2d::Sprite* bgLite2;
	cocos2d::Sprite* bgLite3;
	cocos2d::Sprite* bg;

	cocos2d::Sprite* fish1;
	cocos2d::Sprite* fish2;
	cocos2d::Sprite* fish3;

	void BubbleAction();
	void ButtonAction();
	void FishAction();
	void LiteAction();
	void LogoAction();
};

#endif // __HELLOWORLD_SCENE_H__
