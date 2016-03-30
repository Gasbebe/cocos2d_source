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
	Texture2D* texture = TextureCache::sharedTextureCache()->addImage("Icon.png");

	SpriteBatchNode* bach = SpriteBatchNode::createWithTexture(texture, 800);
	this->addChild(bach);

	for (int i = 0; i < 800; i++) {
		int index = (i % 50) * 8;
		int rowIndex = (i / 50) * 8;

		Sprite* temp = Sprite::createWithTexture(texture);
		temp->setPosition(Vec2(index, rowIndex));
		bach->addChild(temp);
	}
    return true;
}
