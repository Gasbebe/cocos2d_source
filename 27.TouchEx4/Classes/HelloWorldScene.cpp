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
	auto label1 = LabelTTF::create("fixed priority",
		"Arial", 20);
	label1->setPosition(Vec2(240, 300));
	label1->setColor(Color3B::BLACK);
	this->addChild(label1);

	auto label2 = LabelTTF::create("fixed priority\n",
		"작은수가 더 높은 순위를 가집니다"
		"Arial", 20);
	label2->setPosition(Vec2(240, 270));
	label2->setColor(Color3B::BLACK);
	this->addChild(label2);

	sprite1 = new Monster();
	sprite1->setTexture("Images/CyanSquare.png");
	sprite1->setPosition(Vec2(260, 160) + Vec2(-80, 80));
	sprite1->setPriority(10);
	this->addChild(sprite1);

	sprite2 = new Monster();
	sprite2->setTexture("Images/MagentaSquare.png");
	sprite2->setPosition(Vec2(260, 160) + Vec2(-80, 80));
	sprite1->setPriority(20);
	this->addChild(sprite2);

	sprite3 = new Monster();
	sprite3->setTexture("Images/YellowSquare.png");
	sprite3->setPosition(Vec2(260, 160) + Vec2(-80, 80));
	sprite1->setPriority(30);
	sprite2->addChild(sprite3);

    return true;
}
