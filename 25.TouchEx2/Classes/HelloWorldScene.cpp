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

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
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
	auto listener = EventListenerTouchAllAtOnce::create();

	//이벤트 리스너등록
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	//터치리스너의 우선순위를 노드가 화면에 그려진 순서대로 한다
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);

	Layer::onExit();
}

void HelloWorld::onTouchBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToWorldSpace(touchPoint);

	/*
	for (auto &item : touches) {  //터치에 수만큼 반복문 실행 item에 저장
	auto touch = item;
	auto touchPoint = touch->getLocation();

	log("onTouchMove id =%d, x = %f, y = %f",
	touch->getID(),
	touchPoint.x,
	touchPoint.y);
	}
	*/

	log("onTouchMove id =%d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

//움직이면 호출
void HelloWorld::onTouchMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToWorldSpace(touchPoint);

	/*
	for (auto &item : touches) {  //터치에 수만큼 반복문 실행 item에 저장
		auto touch = item;
		auto touchPoint = touch->getLocation();

		log("onTouchMove id =%d, x = %f, y = %f",
			touch->getID(),
			touchPoint.x,
			touchPoint.y);
	}
	*/
	log("onTouchMove id =%d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

//손가락을 화며에서 때면 호출
void HelloWorld::onTouchEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
	auto touch = touches[0];
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToWorldSpace(touchPoint);

	/*
	for (auto &item : touches) {  //터치에 수만큼 반복문 실행 item에 저장
	auto touch = item;
	auto touchPoint = touch->getLocation();

	log("onTouchMove id =%d, x = %f, y = %f",
	touch->getID(),
	touchPoint.x,
	touchPoint.y);
	}
	*/

	log("onTouchEnd id =%d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);
}

//시스템이 터치를 중지시키는경우 호출됨  ex 전화올떄
void HelloWorld::onTouchCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event) {
}
