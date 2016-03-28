#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();   
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
	///////////////////////////////////////////////////
	// type 1: from Sprite                                
    ///////////////////////////////////////////////////

	//
	auto sprite = Sprite::create("grossini_dance_atlas.png");
	//auto texture = sprite->getTexture();
	
	///////////////////////////////////////////////////
	// type 2: from Sprite
	///////////////////////////////////////////////////
	
	//auto texture2 = Director::getInstance()->getTextureCache()->addImage("grossini_dance_atlas.png");

	///////////////////////////////////////////////////
	// type 3: from Sprite
	///////////////////////////////////////////////////

	auto batch = SpriteBatchNode::create("grossini_dance_atlas.png", 10);
	auto texture = batch->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 14; i++) {
		int colum = i % 5; // 0,1,2,3,4
		int row = i / 5; //0,1,2
		// x,y 좌표 x로 얼마만큼  y로 얼마만큼
		animation->addSpriteFrameWithTexture(texture, Rect(colum * 85, row * 121, 85, 121));
	}

	auto pMan = Sprite::create("grossini_dance_atlas.png", Rect(0, 0, 85, 121));
	pMan->setPosition(Vec2(240, 160));
	//auto pMan = Sprite::createWithTexture(texture, Rect(0, 0, 85, 121));
	this->addChild(pMan);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pMan->runAction(rep);

    return true;
}
