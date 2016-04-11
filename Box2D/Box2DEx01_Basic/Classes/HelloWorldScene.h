#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define PTM_RATIO 32

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	~HelloWorld();

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void tick(float dt);
	void addNewSpriteAtPosition(cocos2d::Vec2 location);

	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	b2World* _world;
};

#endif // __HELLOWORLD_SCENE_H__
