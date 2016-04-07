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
	pSprite1 = Sprite::create("Images/grossinis_sister1.png");
	pSprite1->setPosition(Vec2(240, 200));
	this->addChild(pSprite1);

	pSprite2 = Sprite::create("Images/grossinis_sister2.png");
	pSprite2->setPosition(Vec2(240, 200));
	this->addChild(pSprite2);

	pSprite1->setVisible(false);
	pSprite2->setVisible(true);

	auto item = CCMenuItemFont::create(
		"Sprite Flip",
		CC_CALLBACK_1(HelloWorld::doFrontFlip, this));
	item->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(item, nullptr);

	pMenu->setPosition(Vec2(240, 40));

	this->addChild(pMenu);

	return true;
}

void HelloWorld::doFrontFlip(Ref* sender) {
	auto firstHalf = OrbitCamera::create(
		0.5f,
		1.0f, 0,
		0, 90.0f,
		0, 0);

	if (pSprite1->isVisible()) {
		pSprite1->runAction(firstHalf);
	}
	else {
		pSprite2->runAction(firstHalf);
	}

	auto action = Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create(CC_CALLBACK_0(HelloWorld::doBackFlip, this, this)),
		nullptr
		);
	this->runAction(action);
}

void HelloWorld::doBackFlip(Ref* sender) {
	if (pSprite1->isVisible()) {
		pSprite1->setVisible(false);
		pSprite2->setVisible(true);
	}
	else {
		pSprite1->setVisible(true);
		pSprite2->setVisible(false);
	}

	auto secondHalf = OrbitCamera::create(
		0.5f,
		1.0f, 0,
		270, 90.0f,
		0, 0);

	if (pSprite1->isVisible()) {
		pSprite1->runAction(secondHalf);
	}
	else {
		pSprite2->runAction(secondHalf);
	}
}
