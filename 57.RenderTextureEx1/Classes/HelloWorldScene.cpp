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

	m_pTarget = RenderTexture::create(winSize.width,
		winSize.height,
		Texture2D::PixelFormat::RGBA8888);

	m_pTarget->retain();
	m_pTarget->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(m_pTarget, 1);

	MenuItemFont::setFontSize(16);
	auto item1 = MenuItemFont::create("save image", CC_CALLBACK_1(HelloWorld::saveImage, this));
	item1->setColor(Color3B::BLACK);

	auto item2 = MenuItemFont::create("clear", CC_CALLBACK_1(HelloWorld::clearImage, this));
	item2->setColor(Color3B::BLACK);

	auto menu = Menu::create(item1, item2, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(winSize.width - 80, winSize.height - 30));
	this->addChild(menu, 3);

    return true;
}

HelloWorld::~HelloWorld() {
	m_pTarget->release();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void HelloWorld::onEnter() {

	Layer::onEnter();
	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event* event) {
	auto touch = touches[0];
	Vec2 start = touch->getLocation();
	Vec2 end = touch->getPreviousLocation();

	// begin 과 end 사이 있는것을 저장
	m_pTarget->begin();

	float distance = start.getDistance(end);
	if (distance > 1) {
		int d = (int)distance;
		m_pBrush.clear();

		for (int i = 0; i < d; ++i) {
			Sprite* sprite = Sprite::create("Images/brush2.png");
			sprite->setColor(Color3B::RED);
			//sprite->setOpacity(20);
			//sprite->setOpacity(150);
			m_pBrush.pushBack(sprite);
		}
		for (int i = 0; i < d; i++) {

			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;

			m_pBrush.at(i)->setPosition(Vec2(start.x + (difx*delta), start.y + (dify* delta)));
			m_pBrush.at(i)->setRotation(rand() % 360);

			float r = (float)(rand() % 50 / 50.f) + 0.25f;
			m_pBrush.at(i)->setScale(r);
			m_pBrush.at(i)->visit();
		}
	}
	m_pTarget->end();
}

void HelloWorld::saveImage(Ref* sender) {

	static int counter = 0;
	char png[20];
	sprintf(png, "image-%d.png", counter);


	//Type 2

	m_pTarget->saveToFile(png, Image::Format::PNG, true, nullptr);

	//화면 캡쳐부분 밑에하단에 보여줌
	auto image = m_pTarget->newImage();
	auto tex = Director::getInstance()->getTextureCache()->addImage(image, png);

	CC_SAFE_DELETE(image);

	auto sprite = Sprite::createWithTexture(tex);

	sprite->setScale(0.3f);
	sprite->setPosition(Vec2(40, 40));
	sprite->setRotation(counter * 3);

	addChild(sprite);

	Director::getInstance()->getRenderer()->render();
	log("Image saved %s", png);

	counter++;
}

void HelloWorld::clearImage(Ref* sender) {

	m_pTarget->clear(255, 255, 255, 255);

}