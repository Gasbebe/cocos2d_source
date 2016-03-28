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
	statusLabel = LabelTTF::create("No custom event received!", "", 20);
	statusLabel->setColor(Color3B::BLACK);
	statusLabel->setPosition(Vec2(240, 250));
	this->addChild(statusLabel);

	auto pMenuItem1 = MenuItemFont::create("send custom event1",
		CC_CALLBACK_1(HelloWorld::doClick1, this));
	pMenuItem1->setColor(Color3B::BLACK);
	pMenuItem1->setPosition(Vec2(240, 160));

	auto pMenuItem2 = MenuItemFont::create("send custom event2",
		CC_CALLBACK_1(HelloWorld::doClick2, this));
	pMenuItem2->setColor(Color3B::BLACK);
	pMenuItem2->setPosition(Vec2(240, 140));
	
	auto menu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);

    return true;
}
void HelloWorld::onEnter() {
	Layer::onEnter();

	_listener1 = EventListenerCustom::create("game_custom_event1", CC_CALLBACK_1(HelloWorld::doEvent1, this));
	_eventDispatcher->addEventListenerWithFixedPriority(_listener1, 1);

	_listener2 = EventListenerCustom::create("game_custom_event2", CC_CALLBACK_1(HelloWorld::doEvent2, this));
	_eventDispatcher->addEventListenerWithFixedPriority(_listener2, 1);

	
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(_listener1);
	_eventDispatcher->removeEventListener(_listener2);

	Layer::onExit();
}

void HelloWorld::doClick1(Ref* pSender) {
	static int count = 0;
	++count;
	char* buf = new char[10];
	std::sprintf(buf, "%d", count);

	EventCustom event("game_custom_event1");
	event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&event);
}

void HelloWorld::doClick2(Ref* pSender) {
	static int count = 0;
	++count;
	char* buf = new char[10];
	std::sprintf(buf, "%d", count);

	EventCustom event("game_custom_event2");
	event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&event);
}

void HelloWorld::doEvent1(EventCustom* event) {
	std::string str("custom event 1 recevied, ");
	char* buf = static_cast<char*>(event->getUserData());
	str += buf;
	str += " times";
	statusLabel->setString(str.c_str());
	delete[]  buf;
}

void HelloWorld::doEvent2(EventCustom* event) {
	std::string str("custom event 2 recevied, ");
	char* buf = static_cast<char*>(event->getUserData());
	str += buf;
	str += " times";
	statusLabel->setString(str.c_str());
	delete[]  buf;
}