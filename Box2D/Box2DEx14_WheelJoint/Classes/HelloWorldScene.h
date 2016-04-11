#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32
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

	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype,
		const char* spriteName, int type);

	//b2Body* getBodyAtTab(Vec2 p);
	//virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	bool createBox2dWorld(bool debug);
	void tick(float dt);

	cocos2d::Size winSize;
	cocos2d::Texture2D* texture;
	b2World* _world;
	GLESDebugDraw* m_debugDraw;



	b2Body *body0;
	b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;
	b2WheelJointDef jd1;
	b2WheelJointDef jd2;
	void Speed();
protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
