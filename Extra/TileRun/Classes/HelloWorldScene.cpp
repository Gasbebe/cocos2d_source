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

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////
	winSize = Director::getInstance()->getWinSize();
	tmap = TMXTiledMap::create("RunTile.tmx");
	background = tmap->getLayer("Background");
	
	Check = tmap->getLayer("Check");
	Check->setVisible(false);
	this->addChild(tmap, 0, 11);

	auto objects = tmap->getObjectGroup("Spwan");
	//TMXObjectGroup* objects = tmap->getObjectGroup("Objects");
	ValueMap spawnPoint = objects->getObject("SpwanPoint");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	playerPosition = Vec2(x, y);

	this->createPlayer();
	this->schedule(schedule_selector(HelloWorld::MoveBackgoround));
	this->schedule(schedule_selector(HelloWorld::CheckBackground));

	return true;
}


void HelloWorld::createPlayer() {
	player = Sprite::create("grossini.png");

	player->setPosition(playerPosition);
	player->setScale(0.5);
	this->addChild(player);
}

void HelloWorld::MoveBackgoround(float t) {
	

	TMXTiledMap* node = (TMXTiledMap*)this->getChildByTag(11);
	Vec2 newPos = node->getPosition();

	if (newPos.x < -540) {
		newPos.x = 0;
	}
	newPos.x -= 1;
	node->setPosition(newPos);
}
void HelloWorld::CheckBackground(float t) {
	setPlayerPosition(playerPosition);
}

Vec2 HelloWorld::tileCoordForPosition(Vec2 position) {
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height -1;
	return Vec2(x, y);
	//Vec2 point = this->background->convert
}

void HelloWorld::setPlayerPosition(Vec2 position) {
	Vec2 tileCoord = this->tileCoordForPosition(position);
	int tileGid = this->Check->getTileGIDAt(tileCoord);
	if (tileGid) {
		log("!");
		Value properties = tmap->getPropertiesForGID(tileGid);
		log("on");
		if (properties.isNull()) {
			std::string wall = properties.asValueMap()["BgNull"].asString();
			if (wall == "YES") {
				log("낭떠러지");
				return;
			}
		}
	}
}