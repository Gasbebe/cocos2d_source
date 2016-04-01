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
	winSize = Director::getInstance()->getWinSize();

	player = Sprite::create("turret.png");
	
	//터렛 탐의 이미지
	player->setPosition(Vec2(player->getContentSize().width / 2 + 80,
		winSize.height / 2));
	this->addChild(player);

	//총알벡터 초기화
	projectiles.clear();
	//상태변수 초기화
	bProjectile = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	if (bProjectile) {
		return true;
	}
	else {
		bProjectile = true;
	}
	auto touchPoint = touch->getLocation();
	
	//총알생성
	auto nextProjectile = Sprite::create("bullet2.png");

	//회전해야할각도
	Vec2 shootVector = touchPoint - player->getPosition();
	float shootAngle = shootVector.getAngle();
	float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

	//회전시간을 정한다
	float curAngle = player->getRotation();
	float rotateDiff = cocosAngle - curAngle;
	if (rotateDiff > 180)
		rotateDiff -= 360;
	if (rotateDiff < -180)
		rotateDiff += 360;
	float rotateSpeed = 0.5f / 180;
	float rotateDuration = fabsf(rotateDiff * rotateSpeed);

	auto actRotate1 = RotateTo::create(rotateDuration, cocosAngle);
	auto seqAct1 = Sequence::create(actRotate1, CallFunc::create(CC_CALLBACK_0(HelloWorld::finishRotate, this, nextProjectile)),
		nullptr);

	player->runAction(seqAct1);

	shootVector.normalize();
	Vec2 overshorVector = shootVector * 420;
	
	nextProjectile->setRotation(cocosAngle);

	auto actMove2 = MoveBy::create(1.0f, overshorVector);
	auto seqAct2 = Sequence::create(actMove2,
		CallFunc::create(CC_CALLBACK_0(HelloWorld::spriteMoveFinished, this, nextProjectile)),
		nullptr);

	nextProjectile->runAction(seqAct2);
	return true;
}
void HelloWorld::finishRotate(Ref* sender) {
	Sprite* sprite = (Sprite*)sender;

	Vec2 nPos1 = Vec2(player->getContentSize().width, player->getContentSize().height / 2);
	Vec2 nPos2 = player->convertToWorldSpace(nPos1);

	sprite->setPosition(nPos2);

	this->addChild(sprite);

	projectiles.pushBack(sprite);
	bProjectile = false;
}
void HelloWorld::spriteMoveFinished(Ref* sender) {
	Sprite* sprite = (Sprite*)sender;
	this->removeChild(sprite, true);
	projectiles.eraseObject(sprite);
}