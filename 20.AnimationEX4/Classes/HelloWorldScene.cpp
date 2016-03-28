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
	auto cache = SpriteFrameCache::getInstance();
	//첫번쨰 스프라이트

	cache->addSpriteFramesWithFile("animations/grossini_family.plist");

	//두번쨰 스프라이트 시트의 위치 정보 파일을 읽어들인다
	cache->addSpriteFramesWithFile("animations/grossini.plist");

	//세번쨰 개별 스프라이트를 직접 추가한다
	auto pSprite = SpriteFrame::create("animations/blocks9.png", Rect(0, 0, 96, 96));
	cache->addSpriteFrame(pSprite, "blocks9.png");

	//form1
	auto pWoman = Sprite::createWithSpriteFrameName("grossinis_sister1.png");
	pWoman->setPosition(Vec2(120, 220));
	this->addChild(pWoman);

	//form2
	auto pMan = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
	pMan->setPosition(Vec2(240, 220));
	this->addChild(pMan);

	//form3
	auto pBox = Sprite::createWithSpriteFrameName("blocks9.png");
	pBox->setPosition(Vec2(360, 220));
	this->addChild(pBox);
	

	//Texture cache 는 하나의 텍스처만을 반환하므로 이전것을 사용할수 없다.
	//나중에 또 사용하려면 SpriteFrameCahe에 createWithTexture 로 저장해야한다

	//첫번째로드
	auto texture = Director::getInstance()->getTextureCache()->addImage("animations/grossini_dance_atlas.png");

	//스프라이트 생성초기화
	auto pMan2 = Sprite::createWithTexture(texture, Rect(0, 0, 85, 121));
	pMan2->setPosition(Vec2(120, 100));
	this->addChild(pMan2);

	//두번째
	texture = Director::getInstance()->getTextureCache()->addImage("animations/dragon_animation.png");

	//스프라이트 생성 및 초기화
	auto pDragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	pDragon->setPosition(Vec2(240, 100));
	this->addChild(pDragon);

	//세번쨰 로드
	Director::getInstance()->getTextureCache()->addImageAsync("animations/blocks9.png",CC_CALLBACK_1(HelloWorld::imageLoaded, this));
	
	return true;
}

void HelloWorld::imageLoaded(Ref* pSender) {
	auto tex = static_cast<Texture2D*>(pSender);
	auto sprite = Sprite::createWithTexture(tex);
	sprite->setPosition(Vec2(360, 100));
	this->addChild(sprite);
	log("image load  :  %p", pSender);
}
