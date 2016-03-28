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

	auto BathNode = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 50);
	this->addChild(BathNode, 0, 1);

	auto texture = BathNode->getTexture();

	for (int i = 0; i < 14; i++) {
		int colum = i % 5;
		int row = i / 5;

		auto pTemp = Sprite::createWithTexture(texture, Rect(colum * 85, row * 121, 85, 121));
		pTemp->setPosition(Vec2(colum * 85, row * 121));
		BathNode->addChild(pTemp);
	}
    return true;
}
