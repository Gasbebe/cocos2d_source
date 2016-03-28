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
    
    ////////////////////////////////////////////
	//메뉴에 위치는 vec2::zero로 지정해두고
	// 각 메뉴 아이템의 위치를 지정하는 방법
	//메뉴레이어 <- 눈에보이지 않는다
	//디폴트 포인트를 240, 160 -> 0, 0 으로 바꾼다
	////////////////////////////////////////////
	auto pMenuItem = MenuItemImage::create(
		"Images/btn-play-normal.png",
		"Images/btn-play-selected.png",
		CC_CALLBACK_1(HelloWorld::menuSelect, this));

	auto pMenu = Menu::create(pMenuItem, nullptr);

	pMenu->setPosition(Vec2::ZERO);
	
	this->addChild(pMenu);

    return true;
}

void HelloWorld::menuSelect(Ref* pSender) {
	log("메뉴가 선택 되었습니다");
}