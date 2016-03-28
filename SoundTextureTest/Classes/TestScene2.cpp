#include "TestScene2.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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

Scene*TestScene2::createScene() {
	auto scene = Scene::create();
	auto layer = TestScene2::create();
	scene->addChild(layer);

	return scene;
}
bool TestScene2::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 255, 0, 255)))
	{
		return false;
	}

	/////////////////////////////
	auto item1 = MenuItemFont::create("close Scene2",
		CC_CALLBACK_1(TestScene2::doClose, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, nullptr);

	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);

	log("SecondScene INIT");

	return true;
}
void TestScene2::onEnter() {

	Layer::onEnter();

	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
	auto pWoman = Sprite::createWithSpriteFrameName("grossinis_sister1.png");
	pWoman->setPosition(Vec2(120, 220));
	this->addChild(pWoman);
	log("SecondScene :: onEnter");
}
void TestScene2::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("Second:: onEnterTransitionDidFinish");
}

void TestScene2::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("Second:: onExitTransitionDidStart");
}

void TestScene2::onExit() {
	Layer::onExit();
	log("Second:: onExit");
}
TestScene2::~TestScene2() {
	log("Second:: SecondScene dealloc");
}
void TestScene2::doClose(Ref*pSender) {
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);

}