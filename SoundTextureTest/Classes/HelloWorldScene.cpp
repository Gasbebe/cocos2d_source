#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "TestScene2.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_FILE	"Sound/effect2.ogg"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
#define EFFECT_FILE	"Sound/effect1.raw"
#else
#define EFFECT_FILE "Sound/effect1.wav"
#endif // CC_PLATFORM_ANDROID

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE	"Sound/music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#define MUSIC_FILE	"Sound/background.ogg"
#else
#define MUSIC_FILE "Sound/background.mp3"
#endif // CC_PLATFORM_WIN32

using namespace cocos2d;
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
	auto cache = SpriteFrameCache::getInstance();
	//첫번쨰 스프라이트
	cache->addSpriteFramesWithFile("animations/grossini_family.plist");

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_FILE);

	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);

	auto item1 = MenuItemFont::create("pushScene",
		CC_CALLBACK_1(HelloWorld::doChangeScene, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, nullptr);

	this->addChild(pMenu);
	log("HelloWorld INIT");

	return true;
}

void HelloWorld::doChangeScene(Ref* pSender) {
	auto pScene = TestScene2::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	log("Hellow :: onEneter");
}

void HelloWorld::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("HelloWorld:: onEnterTransitionDidFinish");
}

void HelloWorld::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("HelloWorld:: onExitTransitionDidStart");
}

void HelloWorld::onExit() {
	Layer::onExit();
	log("HelloWorld:: onExit");
}

HelloWorld::~HelloWorld() {
	log("HelloWorld:: ~HelloWorld  dealloc");
}
