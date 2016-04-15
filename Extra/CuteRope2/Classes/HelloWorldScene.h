#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#include "vrope.h"
#include "vstick.h"
#include "vpoint.h"

//#define PTM_RATIO 32
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	~HelloWorld();
	
	
	virtual void onEnter();
	virtual void onExit();

	b2Body* addNewSpriteAt(Vec2 point);
	
	//touch, draw
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	
	bool createBox2dWorld(bool debug);
	bool checkLineIntersection(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4);
	b2Body* createRopeTipBody();
	void createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body*bodyB, b2Vec2 anchorbB, float32 sag);
	void tick(float dt);
	void deletePine();
	void changeCrocSprite();

private:
	std::vector<b2Body*> *pinesBody;
	std::vector<VRope*> *ropes;
	b2Body *groundBody;

	cocos2d::SpriteBatchNode* ropeSpriteSheet;

	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	b2World* _world;
	GLESDebugDraw* m_debugDraw;

	bool bPine;
	
	b2Body* dragBody;
	b2MouseJoint* mouseJoint;
	b2Body *gbody;
	cocos2d::Sprite* pine;
	cocos2d::Sprite* croc_;
	b2Body* crocMouth_;
	b2Fixture* crocMouthBottom;
	bool crocMouthOpened;

	protected:
		void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
		cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
