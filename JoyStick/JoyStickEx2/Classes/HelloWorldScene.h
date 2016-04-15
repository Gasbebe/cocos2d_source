#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Joystick.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>
#define  PTM_RATIO 32

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
		
	Joystick* joystick;
	cocos2d::Sprite* pMan;
	void tick(float dt);

	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	b2Body *addNewSprite(cocos2d::Vec2 point, cocos2d::Size size, b2BodyType bodytype, const char* spriteName, int type);
	bool createBox2dWorld(bool debug);

	cocos2d::Size winSize;
	b2Body* body; 
	cocos2d::Texture2D* texture;
	b2World* _world;

	//for debuging
	GLESDebugDraw* m_debugDraw;
protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
