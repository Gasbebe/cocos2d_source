#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	void log2(const char *pszFormat, ...);
#endif
};

#endif // __HELLOWORLD_SCENE_H__
