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
    
    /////////////////////////////
	auto sprite = Sprite::create("Images/grossinis_sister.png");

	pt = ProgressTimer::create(sprite);
	pt->setType(ProgressTimer::Type::RADIAL);
	pt->setPosition(Vec2(240, 160));
	this->addChild(pt);
	nNum = 0;

	this->schedule(schedule_selector(HelloWorld::myTick), 0.1f);

    return true;
}

void HelloWorld::myTick(float t) {
	nNum++;
	this->SpriteProgressToRabial(nNum * 2);
	if (nNum > 50) {
		nNum = 0;
	}
	
}

void HelloWorld::SpriteProgressToRabial(float f) {
	pt->setPercentage(f);
}