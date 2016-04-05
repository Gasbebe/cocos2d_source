#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include "pugixml/pugixml.hpp"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	int nullPosition = 8;
	int temp;
	int count = 0;
	cocos2d::Sprite* sildePuzzle[8];
	cocos2d::Size size;
	cocos2d::Vec2 puzzlePosition[9];

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void CheckNullPosition();
	void SwapPosition(int i, int puzzleNum);
	void initSuffle();
};

#endif // __HELLOWORLD_SCENE_H__
