#include "TestScene1.h"

USING_NS_CC;

Scene* TestScene1::createScene()
{
	auto scene = Scene::create();
	auto layer = TestScene1::create();
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestScene1::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 255, 0, 255)))
	{
		return false;
	}

	/////////////////////////////
	auto item1 = MenuItemFont::create("Close Scene2",
		CC_CALLBACK_1(TestScene1::doClose, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);
	return true;
}
void TestScene1::doClose(Ref* pSender) {
	Director::getInstance()->popScene();
}
