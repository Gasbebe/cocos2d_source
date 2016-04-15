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
	joystick = Joystick::create();
	this->addChild(joystick, 2);

	//
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	this->schedule(schedule_selector(HelloWorld::tick));

    return true;
}

void HelloWorld::tick(float t) {
	float width = pMan->getContentSize().width / 2;
	float height = pMan->getContentSize().height / 2;

	float vx = pMan->getPosition().x + joystick->getVelocity().x;
	float vy = pMan->getPosition().y + joystick->getVelocity().y;

	if ((vx < width) || (vx > (480-width))) {
		vx = pMan->getPosition().x;
	}

	if ((vy < height) || (vy >(320 - height))) {
		vy = pMan->getPosition().y;
	}
	pMan->setPosition(Vec2(vx, vy));
}