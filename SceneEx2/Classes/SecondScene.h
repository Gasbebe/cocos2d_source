#ifndef _SceneTrans1_SecondScene_
#define _SceneTrans1_SecondScene_

#include "cocos2d.h"
USING_NS_CC;

class SecondScene : public cocos2d::LayerColor{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SecondScene);

	void onEnter();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();
	void onExit();
	~SecondScene(void);

	void doClose(Ref* pSender);

};
#endif // !_SceneTrans1_SecondScene_

