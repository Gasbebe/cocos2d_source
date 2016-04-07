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
	Size winSize = Director::getInstance()->getWinSize();

	auto bgLayer = LayerColor::create(
		Color4B(0, 255, 0, 255),
		winSize.width, winSize.height);
	bgLayer->setAnchorPoint(Vec2(0, 0));
	bgLayer->setRotation3D(cocos2d::Vertex3F(-20.0, 0.0, 0.0));
	this->addChild(bgLayer);

	auto bgSprite = Sprite::create("Images/HelloWorld.png");
	bgSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bgLayer->addChild(bgSprite);

	man = Sprite::create("Images/grossini.png");
	man->setPosition(Vec2(245, -50));
	bgLayer->addChild(man);

	auto act = MoveBy::create(2.0f, Vec2(0, 450));
	auto seq = Sequence::create(Place::create(Vec2(240,-50)),
		act,
		nullptr);
	auto rep = RepeatForever::create(seq);
	man->runAction(rep);


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	auto touchPoint = touch->getLocation();

	log("onTouchBegan id =%d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);

	bool bTouch = man->getBoundingBox().containsPoint(touchPoint);
	if (bTouch) {
		log("sprite touch");
	}
	return true;
}
