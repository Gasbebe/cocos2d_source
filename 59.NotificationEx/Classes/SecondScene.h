#ifndef __PopupTouchEx__SecondScene__
#define __PopupTouchEx__SecondScene__

#include "cocos2d.h"

USING_NS_CC;

class SecondScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SecondScene);

	void doSendMsg(Ref* pSender);
	void doClose(Ref* pSender);
};

#endif // __PopupTouchEx__SecondScene__
