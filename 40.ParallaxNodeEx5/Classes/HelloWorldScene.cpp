﻿#include "HelloWorldScene.h"

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

	layer1 = Layer::create();
	this->addChild(layer1);
	layer2 = Layer::create();
	this->addChild(layer2);

	winSize = Director::getInstance()->getWinSize();
	this->createBackgroundParallax();
	this->createDragon();
	this->createArrowButtons();
	return true;
}

void HelloWorld::createBackgroundParallax() {

	auto background1 = Sprite::create("background1.png");
	background1->setAnchorPoint(Vec2(0, 0));
	auto background2 = Sprite::create("background2.png");
	background2->setAnchorPoint(Vec2(0, 0));

	background1->getTexture()->setAliasTexParameters();
	background2->getTexture()->setAliasTexParameters();

	auto voidNode = ParallaxNode::create();

	voidNode->addChild(background1, 1, Vec2(1.0f, 1.0f), Vec2(0, 0));
	voidNode->addChild(background2, 1, Vec2(1.0f, 1.0f), Vec2(512, 0));

	auto go = MoveBy::create(4, Vec2(0, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, nullptr);
	auto act = RepeatForever::create(seq);

	voidNode->runAction(act);

	layer1->addChild(voidNode, 0);
}

void HelloWorld::createDragon() {
	auto texture = Director::getInstance()->getTextureCache()->addImage("dragon_animation.png");
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 6; i++) {
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140, 130, 140));
	}
	dragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	dragon->setPosition(Vec2(240, 160));
	layer1->addChild(dragon);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);
}

void HelloWorld::createArrowButtons() {

	leftSprite = Sprite::create("Images/b1.png");
	leftSprite->setPosition(Vec2(180, 30));
	layer2->addChild(leftSprite, 2);

	leftPressSprite = Sprite::create("Images/b2.png");
	leftPressSprite->setPosition(leftSprite->getPosition());
	layer2->addChild(leftPressSprite, 1);

	rightSprite = Sprite::create("Images/f1.png");
	rightSprite->setPosition(Vec2(300, 30));
	layer2->addChild(rightSprite, 2);

	rightPressSprite = Sprite::create("Images/f2.png");
	rightPressSprite->setPosition(rightSprite->getPosition());
	layer2->addChild(rightPressSprite, 1);
}


void HelloWorld::onEnter() {
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	isLeftPressed = false;
	isRightPressed = false;

	if (this->isTouchInside(leftSprite, touch) == true) {
		leftSprite->setVisible(false);
		isLeftPressed = true;
	}
	else if (this->isTouchInside(rightSprite, touch) == true) {
		rightSprite->setVisible(false);
		isRightPressed = true;
	}

	if (isLeftPressed == true || isRightPressed == true) {
		this->startMovingBackground();
	}
	return true;
}
void HelloWorld::onTouchMove(cocos2d::Touch* touch, cocos2d::Event* event) {

	if (isLeftPressed == true && this->isTouchInside(leftSprite, touch) == false) {
		leftSprite->setVisible(true);
		this->stopMovingBackground();
	}
	else if (isRightPressed == true && this->isTouchInside(rightSprite, touch) == false) {
		rightSprite->setVisible(true);
		this->stopMovingBackground();
	}
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	if (isLeftPressed == true || isRightPressed == true) {
		this->stopMovingBackground();
	}
	if (isLeftPressed == true) {
		leftSprite->setVisible(true);
	}
	if (isRightPressed == true) {
		rightSprite->setVisible(true);
	}

}
#pragma mark - 
#pragma mark Game Play
bool HelloWorld::isTouchInside(cocos2d::Sprite* sprite, cocos2d::Touch* touch) {
	auto touchPoint = touch->getLocation();
	auto bTouch = sprite->getBoundingBox().containsPoint(touchPoint);

	return bTouch;
}
void HelloWorld::startMovingBackground() {
	log("start movig");
	this->schedule(schedule_selector(HelloWorld::moveBackground));
}
void HelloWorld::stopMovingBackground() {
	log("stop movig");
	this->unschedule(schedule_selector(HelloWorld::moveBackground));
}
void HelloWorld::moveBackground(float t) {
	log("move background");

	auto moveStep = 3;
	if (isLeftPressed) {
		moveStep = -3;
		dragon->setFlippedX(false);
	}
	else
	{
		moveStep = 3;
		dragon->setFlippedX(true);
	}

	auto newPos = Vec2(dragon->getPosition().x + moveStep, dragon->getPosition().y);
	if (newPos.x < 0) {
		newPos.x = 0;
	}
	else if (newPos.x > 512 * 2) {
		newPos.x = 512 * 2;
	}
	dragon->setPosition(newPos);
	//카메라가 따라다님   x = 1024 크기 y = 320크기  크기로 정해진 만큼의 좌표만 따라다님
	layer1->runAction(Follow::create(dragon, Rect(0, 0, 512 * 2, 320)));
}