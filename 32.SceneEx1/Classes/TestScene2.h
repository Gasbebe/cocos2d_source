#ifndef __TEST_SCENE2_
#define __TEST_SCENE2_

#include "cocos2d.h"

class TestScene2 : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene2);
	void doClose(Ref* pSender);
};

#endif // __HELLOWORLD_SCENE_H__
