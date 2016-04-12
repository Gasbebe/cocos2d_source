#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

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
	//메뉴 생성부분
	winSize = Director::getInstance()->getWinSize();

	auto bg = Sprite::create("Images/background.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	auto logo = Sprite::create("Images/logo.png");
	logo->setPosition(Vec2(winSize.width / 2, winSize.height / 2 + 200));
	logo->setScale(0.8f);
	this->addChild(logo);

	auto starParticles = ParticleSystem::create("particles/bg-stars.plist");
	this->addChild(starParticles);
	
	auto playMenuItem = MenuItemImage::create("Images/btn-play.png",
												"Images/btn-play-down.png",
												CC_CALLBACK_0(HelloWorld::onPressPlay, this));

	playMenuItem->setPosition(Vec2(winSize.width / 2, winSize.height / 2-100));

	auto aboutMenuItem = MenuItemImage::create("Images/btn-about.png",
												"Images/btn-about-down.png",
												CC_CALLBACK_0(HelloWorld::onPressPlay, this));

	aboutMenuItem->setPosition(Vec2(winSize.width / 2, winSize.height / 2 -300));

	auto menu = Menu::create(playMenuItem, aboutMenuItem, nullptr);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);
	
	int menuSelection = kMenuSelectionPlay;
	
	auto act = Sequence::create(ScaleBy::create(0.3, 0), ScaleTo::create(0.3, 0.8),
		ScaleTo::create(0.2, 0.7), ScaleTo::create(0.2, 0.8),nullptr);

	logo->runAction(act->clone());
	playMenuItem->runAction(act->clone());
	aboutMenuItem->runAction(act->clone());

	//sound
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sounds/loop.mp3");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/loop.mp3", true);

    return true;
}
void HelloWorld::onPressPlay() {
	auto pScene = GameScene::createScene();
	Director::getInstance()->pushScene(pScene);
}
