#ifndef _SceneTrans2_SecondScene_
#define _SceneTrans2_SecondScene_

#include "cocos2d.h"
USING_NS_CC;

class TestScene2 : public cocos2d::LayerColor {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TestScene2);
	void onEnter();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();
	void onExit();
	~TestScene2(void);

	void doClose(Ref* pSender);

};
#endif // !_SceneTrans1_SecondScene_

