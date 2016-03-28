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

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

    return true;
}

void HelloWorld::onEnter() {
	//씬이시작될떄 호출
	Layer::onEnter();

	//싱클터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	//swallow
	//겹치지않게 터치됨
	listener->setSwallowTouches(true);

	//이벤트 리스너등록
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	
	//터치리스너의 우선순위를 노드가 화면에 그려진 순서대로 한다
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	log("onTouchBegan id =%d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);

	bool bTouch = pMan->getBoundingBox().containsPoint(touchPoint);
	if (bTouch) {
		log("sprite touch");
	}
	return true;
}

//움직이면 호출
void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	log("onTouchMove id =%d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

//손가락을 화며에서 때면 호출
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	log("onTouchEnd id =%d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

//시스템이 터치를 중지시키는경우 호출됨  ex 전화올떄
void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
}
