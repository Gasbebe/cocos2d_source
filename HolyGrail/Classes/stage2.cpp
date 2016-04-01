
#include "stage2.h"
USING_NS_CC;

Scene* Stage1::createScene()
{
	auto scene = Scene::create();
	auto layer = Stage1::create();
	scene->addChild(layer);

	return scene;
}

bool Stage1::init()
{

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////
	winSize = Director::getInstance()->getWinSize();
	tmap = TMXTiledMap::create("stage2.tmx");
	background = tmap->getLayer("Background");
	items = tmap->getLayer("Items");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);

	TMXObjectGroup* objects = tmap->getObjectGroup("Object");
	ValueMap spawnPoint = objects->getObject("SpawnPoint");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	HeroPosition = Vec2(x, y);
	hello = new HelloWorld();
	hello->HeroPosition = this->HeroPosition;
	hello->createHero();
	//this->createHero();

	return true;
}