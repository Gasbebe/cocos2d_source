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
	//스프라이트todtjd
	auto pMan = Sprite::create("Images/grossini.png");

	//스프라이트 위치지정
	pMan->setPosition(Vec2(240, 160));

	//레이어에 스프라이트 객체추가
	this->addChild(pMan);

	//코드추가

	auto pWoman = Sprite::create("Images/grossinis_sister1.png");
	pWoman->setPosition(Vec2(260, 160));
	this->addChild(pWoman, 1);

	//스프라이트 위치 동적지정
	pMan->setLocalZOrder(1);

    return true;
}
