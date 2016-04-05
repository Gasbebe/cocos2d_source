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
	auto pLabel3 = LabelTTF::create("hello", "Arial",32);
	pLabel3->setPosition(Vec2(240, 200));
	pLabel3->setColor(Color3B::BLACK);
	this->addChild(pLabel3);

	//비트맵 폰트 파일 사용법
	//사용하려면 fnt , png파일이 필요하고  해당 글자는 반드시 파일안에 있어야한다
	auto pLabel = LabelBMFont::create("hello", "fonts/futura-48.fnt");
	pLabel->setPosition(Vec2(240, 150));
	this->addChild(pLabel);
	
	//캐릭터맵 폰트 파일 사용법
	//itemWidth , itemHeight는 같은 크기의 이미지로 된 스프라이트시트를 이용해
	//스프라이트 시트를 만들떄와 마찬가지로 글자 하나에 해당하는 크기를 나타낸다
	auto pLabel2 = LabelAtlas::create("1234", "fonts/fps_images.png", 12, 32, '.');  //12 ,32 픽셀로 자름    '.'아스키코드값부터 시작 9까지
	pLabel2->setPosition(Vec2(240, 50));
	this->addChild(pLabel2);


    return true;
}
