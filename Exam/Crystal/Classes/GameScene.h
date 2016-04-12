#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "gem.h"

#define PTM_RATIO 32

class GameScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	Gem* gem1;
	cocos2d::Layer* gGameLayer;
	cocos2d::Layer* gParticleLayer;
	cocos2d::Layer* gHintLayer;
	cocos2d::Layer* gShimmerLayer;
	cocos2d::Layer* gEffectsLayer;

	cocos2d::Size winSize;
	cocos2d::Sprite* header;
	cocos2d::Sprite* timeBar;

	CREATE_FUNC(GameScene);

	void setupBoard();
	void removeMarkedGems();
	void findConnectedGems_(int x, int y, std::vector<int> arr, int gemType);
	std::vector<int> findConnectedGems(int x, int y);
	void fallingGem(float t);

	//virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* evnet);
	//virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* evnet);
	
	void tick(float dt);
	void addNewSpriteAtPosition(cocos2d::Vec2 location);
	void createWorld();
	void checkTime(float t);
	b2World* _world;
	cocos2d::Texture2D* texture;
};

#endif // __HELLOWORLD_SCENE_H__
