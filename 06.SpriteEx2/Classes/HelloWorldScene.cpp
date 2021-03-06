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
	/*
	auto parent = Sprite::create("Images/white-512x512.png");
	parent->setTextureRect(Rect(0, 0, 150, 150));
	parent->setPosition(Vec2(240, 160));
	parent->setColor(Color3B(0,0,255));

	this->addChild(parent);

	auto child = Sprite::create("Images/white-512x512.png");
	child->setTextureRect(Rect(0, 0, 50, 50));
	child->setColor(Color3B::RED);
	child->setPosition(Vec2(0, 0));

	parent->addChild(child);
	*/

	auto parent = Sprite::create("Images/white-512x512.png");
	parent->setTextureRect(Rect(0, 0, 150, 150));
	parent->setPosition(Vec2(240, 160));
	parent->setColor(Color3B(0, 0, 255));

	this->addChild(parent);

	
	
	auto child = Sprite::create("Images/white-512x512.png");
	child->setTextureRect(Rect(0, 0, 50, 3));
	child->setColor(Color3B::RED);


	Size parentSize;
	parentSize = parent->getContentSize();
	child->setPosition(Vec2(parentSize.width / 2.0, parentSize.height + 10));

	parent->addChild(child);

    return true;
}
