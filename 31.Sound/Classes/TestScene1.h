#ifndef __TEST_SCENE1_
#define __TEST_SCENE1_

#include "cocos2d.h"

class TestScene1 : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene1);
	void doClose(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
