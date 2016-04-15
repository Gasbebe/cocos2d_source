-#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	~HelloWorld();

	bool playerIsFlying;
	float playerVelocity;

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void tick(float dt);
	void addNewSpriteAtPosition(cocos2d::Vec2 location);
	bool createBox2dWorld(bool debug);
	bool debug;

	void AddForce(float t);

	b2Body* body;
	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	b2World* _world;

	//for debuging
	GLESDebugDraw* m_debugDraw;
	protected:
		void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
		cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
