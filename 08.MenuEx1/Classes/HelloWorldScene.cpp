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
	auto pMenuItem1 = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick1, this));

	auto pMenuItem2 = MenuItemImage::create(
		"Images/btn-highscores-normal.png",
		"Images/btn-highscores-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick2, this));

	auto pMenuIteme3 = MenuItemImage::create(
		"Images/btn-about-normal.png",
		"Images/btn-about-selected.png",
		CC_CALLBACK_1(HelloWorld::doClick3, this));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuIteme3, nullptr);
	pMenu->alignItemsVertically();

	this->addChild(pMenu);
	
	
    return true;
}
	void HelloWorld::doClick1(Ref* pSender) {
		log("첫번쨰 메뉴가 선택");
	}
	void HelloWorld::doClick2(Ref* pSender) {
		log("두번쨰 메뉴가 선택");
	}
	void HelloWorld::doClick3(Ref* pSender) {
		log("세번쨰 메뉴가 선택");
	}