#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32
#define FLOOR_HEIGHT    62.0f

enum
{
	kTagTileMap = 1,
	kTagSpriteManager = 1,
	kTagAnimation1 = 1,
};

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	~HelloWorld();
	bool createBox2dWorld(bool debug);

	virtual void onEnter();
	virtual void onExit();
	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
		cocos2d::Event* event);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches,
		cocos2d::Event* event);
	virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,
		cocos2d::Event* event);
	void tick(float dt);

	void createBullets(int count);
	bool attachBullet();
	void resetBullet();
	void resetGame();

	void createTargets();
	void createTarget(const char *imageName,
		cocos2d::Vec2 position,
		float rotation,
		bool isCircle,
		bool isStatic,
		bool isEnemy);

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);

	cocos2d::CustomCommand _customCmd;

private:
	std::vector<b2Body *> m_bullets;
	std::vector<b2Body *> m_targets;
	std::vector<b2Body *> m_enemies;

	int m_currentBullet;
	b2World* m_world;
	b2Body* m_groundBody;
	b2Fixture *m_armFixture;
	b2Body *m_armBody;
	b2RevoluteJoint *m_armJoint;
	b2MouseJoint *m_mouseJoint;

	b2Body *m_bulletBody;
	b2WeldJoint *m_bulletJoint;


	bool m_releasingArm;
};

#endif
