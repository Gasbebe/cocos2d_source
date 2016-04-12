#ifndef __GEM_H__
#define __GEM_H__

#define PTM_RATIO 32

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class Gem : public cocos2d::Sprite {

public:
	Gem();
	
	int tagNum;
	cocos2d::Vec2 gemPos;
	cocos2d::Size gemSize;
	cocos2d::Sprite* gemSprite;
	void SetTag(int tagnum);
	int GetTag();

	void createBox2D();

	void SetPos(cocos2d::Vec2 pos);
	void SetSize(cocos2d::Size winSize);
	cocos2d::Vec2 GetPos();
	cocos2d::Size GetSize();
	b2World* _world;
	virtual void onEnter();
	virtual void onExit();
private:
	int _fixedPriority;
	bool _useNodePriority;
};
#endif //_SpriteExtendEx_gem


