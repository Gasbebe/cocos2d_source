#include "TestScene2.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* TestScene2::createScene()
{
	auto scene = Scene::create();
	auto layer = TestScene2::create();
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestScene2::init()
{

	if (!LayerColor::initWithColor(Color4B(255, 255, 0, 255)))
	{
		return false;
	}

	/////////////////////////////
	auto item1 = MenuItemFont::create("Close Scene2",
		CC_CALLBACK_1(TestScene2::doClose, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);
	return true;
}
void TestScene2::doClose(Ref* pSender) {
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}
