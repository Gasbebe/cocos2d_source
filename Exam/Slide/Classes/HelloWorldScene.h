﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include "pugixml/pugixml.hpp"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	cocos2d::Sprite* sildePuzzle[8];
};

#endif // __HELLOWORLD_SCENE_H__
