#include "HelloWorldScene.h"
#include "pugixml/pugixml.hpp"

USING_NS_CC;
using namespace pugi;

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
	auto texture = Director::getInstance()->getTextureCache()->addImage("puzzle.png");


	for (int i = 0; i < 8; i++) {
		int x = i%3;
		int row = i/3;
		//position
		sildePuzzle[i] = Sprite::createWithTexture(texture, Rect(x*80, row*80, 80, 80));
		sildePuzzle[i]->setPosition(Vec2(((7-i)%3) * 82 + 100, ((7-i)/3)* 82 + 100));
		this->addChild(sildePuzzle[i]);
	}



    return true;
}
