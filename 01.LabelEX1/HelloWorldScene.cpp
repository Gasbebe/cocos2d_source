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
	
	//레이블 생성 초기화
	//auto pLabel = LabelTTF::create("동해물과 백두산이 마르고 닳도록 하느님이 보우하사", "Arial", 34);
	auto pLabel = LabelTTF::create("동해물과 백두산이 마르고 닳도록 하느님이 보우하사", "Arial", 34,
		Size(300,200),TextHAlignment::CENTER,
		TextVAlignment::CENTER);

	//레이블 색지정
	pLabel->setColor(Color3B::BLACK);// 255,0,0
	//pLabel->setAnchorPoint(Vec2(0, 0.5));

	//레이블의 위치 지정
	pLabel->setPosition(Vec2(240, 160));

	//레이블의 투명도 지정  0~255
	pLabel->setOpacity(100.0);

	//레이블에 레이블 객체 추가
	this->addChild(pLabel);
	
	auto pLabel2 = LabelTTF::create("Hello2", "Arial", 30);

	pLabel2->setColor(Color3B::BLACK);
	pLabel2->setPosition(Vec2(240, 100));
	pLabel2->setOpacity(255.0);   // 
	this->addChild(pLabel2);

    return true;
}
