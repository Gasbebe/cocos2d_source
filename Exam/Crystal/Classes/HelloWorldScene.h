#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	
	enum {
		kMenuSelectionPlay = 1,
		kMenuSelectionAbout = 2,
		
	};
	//0으로 초기화
	cocos2d::Size winSize;
    CREATE_FUNC(HelloWorld);
	void onPressPlay();
	void onPressAbout();
	void onAnimationComplete();
	void onUpdate();
};

#endif // __HELLOWORLD_SCENE_H__
