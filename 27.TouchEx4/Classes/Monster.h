#ifndef _SpriteExtendEx_Monster_
#define _SpriteExtendEx_Monster_

#include "cocos2d.h"

class Monster : public cocos2d::Sprite {
	
public:
	Monster();
	void setPriority(int fixedPriority);
	void setPriorityWithThis(int useNodePriority);

	virtual void onEnter();
	virtual void onExit();

private:
	cocos2d::EventListener* _listener;
	int _fixedPriority;
	bool _useNodePriority;
};
#endif //_SpriteExtendEx_Monster_

