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

    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
    /////////////////////////////
	winSize = Director::getInstance()->getWinSize();
	tmap = TMXTiledMap::create("TileMap/TestDesert.tmx");
	this->addChild(tmap, 0, 11);

	//auto objects = tmap->getObjectGroup("Objects");
	TMXObjectGroup* objects = tmap->getObjectGroup("Objects");
	ValueMap spawnPoint = objects->getObject("SpawnPoint");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	
	dragoPosition = Vec2(x,y);
	this->createDragon();

    return true;
}


void HelloWorld::onEnter() {
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
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
	dragon->setPosition(240, 160);
	dragon->setScale(0.5);
	this->addChild(dragon);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);
}
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	return true;
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = dragon->getPosition();
	Vec2 diff = touchPoint - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += tmap->getTileSize().width;
			dragon->setFlippedX(true);
		}
		else {
			playerPos.x -= tmap->getTileSize().width;
			dragon->setFlippedX(false);
		}

	}
	else {
		if (diff.y > 0) {
			playerPos.y += tmap->getTileSize().height;
		}
		else {
			playerPos.y -= tmap->getTileSize().height;
		}
	}

	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width) &&
		playerPos.y <= (tmap->getMapSize().height * tmap->getTileSize().height) &&
		playerPos.x >= 0 &&
		playerPos.x >= 0) {
		dragon->setPosition(playerPos);
	}
	this->setViewpointCenter(dragon->getPosition());


}
void HelloWorld::setViewpointCenter(Vec2 position) {
	int x = MAX(position.x, (winSize.width / 2));
	int y = MAX(position.y, (winSize.height / 2));

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - (winSize.width / 2));
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - (winSize.height / 2));

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}