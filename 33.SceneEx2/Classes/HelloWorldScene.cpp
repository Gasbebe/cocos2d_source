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
	auto item1 = MenuItemFont::create("pushScene",
		CC_CALLBACK_1(HelloWorld::doChangeScene, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, nullptr);

	this->addChild(pMenu);
	log("HelloWorld INIT");

    return true;
}

void HelloWorld::doChangeScene(Ref* pSender) {
	auto pScene = SecondScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	log("Hellow :: onEneter");
}

void HelloWorld::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("HelloWorld:: onEnterTransitionDidFinish");
}

void HelloWorld::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("HelloWorld:: onExitTransitionDidStart");
}

void HelloWorld::onExit() {
	Layer::onExit();
	log("HelloWorld:: onExit");
}

HelloWorld::~HelloWorld() {
	log("HelloWorld:: ~HelloWorld  dealloc");
}
