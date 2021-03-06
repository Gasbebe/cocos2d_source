﻿#include "HelloWorldScene.h"
#include "SecondScene.h"

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
	auto pMenuItem = MenuItemFont::create(
		"팝업창 띄우기",
		CC_CALLBACK_1(HelloWorld::doPopup, this));
	pMenuItem->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem, nullptr);

	pMenu->setPosition(Vec2(240, 40));

	this->addChild(pMenu);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(HelloWorld::doMsgReceived),
		"TouchStatus",
		nullptr);

    return true;
}

void HelloWorld::doPopup(Ref * obj) {
	Scene* popWin;
	popWin = SecondScene::createScene();
	this->addChild(popWin, 2000, 2000);
}
void HelloWorld::doMsgReceived(Ref* obj) {

	char *inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);

	log("[%s]  메세지 도착", testText);
}