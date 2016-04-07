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
	auto listener = EventListenerTouchOneByOne::create();
	//swallow
	//겹치지않게 터치됨
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::changeCameraAngle, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(240, 160));
	this->addChild(sprite);

	camera = new ActionCamera;
	camera->startWithTarget(this);

    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	return true;
}

void HelloWorld::changeCameraAngle(Touch* touch, Event* unused_event) {

	kmVec3 eye = camera->getEye();
	eye.x -= touch->getDelta().x * 0.0000000001;
	eye.y -= touch->getDelta().y * 0.0000000001;
	camera->setEye(eye);

}