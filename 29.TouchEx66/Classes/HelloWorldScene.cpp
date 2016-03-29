﻿#include "HelloWorldScene.h"
#include "TouchPoint.h"

USING_NS_CC;

static Map<int, TouchPoint*> s_map;

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
	return true;
}

void HelloWorld::onEnter() {
	//씬이시작될떄 호출
	Layer::onEnter();

	//싱클터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchAllAtOnce::create();

	//이벤트 리스너등록
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);

	//터치리스너의 우선순위를 노드가 화면에 그려진 순서대로 한다
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);

	Layer::onExit();
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto location = touch->getLocation();
		auto touchPoint = TouchPoint::touchPointWithParent(this, location, *s_TouchColors[touch->getID() % 5]);

		addChild(touchPoint);
		s_map.insert(touch->getID(), touchPoint);
	}
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto pTP = s_map.at(touch->getID());
		auto location = touch->getLocation();

		removeChild(pTP, true);
		s_map.erase(touch->getID());

		auto touchPointNew = TouchPoint::touchPointWithParent(this, location, *s_TouchColors[touch->getID() % 5]);
		addChild(touchPointNew);
		s_map.insert(touch->getID(), touchPointNew);
	}
}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto pTP = s_map.at(touch->getID());
		removeChild(pTP, true);
		s_map.erase(touch->getID());
	}
}

void HelloWorld::onTouchesCancelled(const std::vector<Touch*>& touches, Event  *event)
{
	onTouchesEnded(touches, event);
}
