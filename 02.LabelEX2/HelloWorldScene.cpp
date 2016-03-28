#include "HelloWorldScene.h"

static std::string fontList[] = {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	"A Damn Mess",
	"Adderancy",
	"Adbuction",
	"Paint Boy",
	"Schwarzald Regular",
	"Scissor Cuts",
#else
	"fonts/A Damn Mess.ttf",
	"fonts/Adderancy.ttf",
	"fonts/Adbuction.ttf",
	"fonts/Paint Boy.ttf",
	"fonts/Schwarzald Regular.ttf",
	"fonts/Scissor Cuts.ttf",
#endif
};


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
	auto pLabel = LabelTTF::create("hello",fontList[5].c_str(), 34);
	pLabel->setPosition(Vec2(240, 100));
	pLabel->setColor(Color3B::BLACK);
	this->addChild(pLabel);


	///////////////////////////
	auto pLabel2 = LabelTTF::create("hello", "Arial", 34);
	pLabel2->setPosition(Vec2(240, 200));
	pLabel2->setColor(Color3B::BLACK);
	this->addChild(pLabel2);

    return true;
}
