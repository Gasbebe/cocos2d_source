#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::extension;

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
	auto sprite1 = Sprite::create("Hello.png");
	auto sprite2 = Sprite::create("Hello.png");

	sprite1->setScale(0.4f);
	sprite2->setScale(0.4f);

	sprite1->setPosition(Vec2(100, 80));
	sprite2->setPosition(Vec2(850, 80));

	auto layer = LayerColor::create(Color4B::GREEN);
	layer->setAnchorPoint(Vec2::ZERO);
	layer->setPosition(Vec2::ZERO);
	layer->setContentSize(Size(960, 160));

	layer->addChild(sprite1);
	layer->addChild(sprite2);

	scrollView = ScrollView::create();
	scrollView->retain();
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setViewSize(Size(480, 160));
	scrollView->setContentSize(layer->getContentSize());
	scrollView->setContentOffset(Vec2::ZERO, false);
	//scrollView->setContentOffset(Vec2(300,0), true);
	scrollView->setPosition(Vec2(0, 100));
	scrollView->setContainer(layer);
	scrollView->setDelegate(this);
	this->addChild(scrollView);
    return true;
}

void HelloWorld::scrollViewDidScroll(ScrollView* view) {
	log("scrollViewDidScroll......");
}

void HelloWorld::scrollViewDidZoom(ScrollView* view) {
	log("scrollViewDidZoom");
}