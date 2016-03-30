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
	auto background1 = Sprite::create("Images/background1.png");
	background1->setAnchorPoint(Vec2(0, 0));
	auto background2 = Sprite::create("Images/background2.png");
	background2->setAnchorPoint(Vec2(0.5, 0));

	background1->getTexture()->setAliasTexParameters();
	background2->getTexture()->setAliasTexParameters();

	auto voidNode = ParallaxNode::create();

	voidNode->addChild(background1, 1, Vec2(1.0f, 1.0f), Vec2(0, 0));
	voidNode->addChild(background2, 1, Vec2(1.0f, 1.0f), Vec2(512, 0));

	auto go = MoveBy::create(4, Vec2(-512, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, nullptr);
	auto act = RepeatForever::create(seq);

	voidNode->runAction(act);

	this->addChild(voidNode);

    return true;
}
