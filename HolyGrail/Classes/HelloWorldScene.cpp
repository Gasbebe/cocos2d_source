#include "HelloWorldScene.h"
#include "stage2.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Holygrail.plist");

	winSize = Director::getInstance()->getWinSize();
	tmap = TMXTiledMap::create("stage1.tmx");
	background = tmap->getLayer("Background");
	items = tmap->getLayer("Items");
	metainfo = tmap->getLayer("MetaInfo");
	monsterSpawn = tmap->getObjectGroup("MonsterSpawn");
	metainfo->setVisible(false);

	this->addChild(tmap, 0, 11);

	objects = tmap->getObjectGroup("Object");

	ValueMap spawnPoint = objects->getObject("SpawnPoint");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	log("%d,   %d", x, y);
	HeroPosition = Vec2(x, y);

	ValueMap monsterSpawnPoint = monsterSpawn->getObject("MonsterSpawn");
	int a = monsterSpawnPoint["x"].asInt();
	int b = monsterSpawnPoint["y"].asInt();
	MonsterPosition = Vec2(a, b);

	ValueMap monsterSpawnPoint1 = objects->getObject("HolySpawn");
	int c = monsterSpawnPoint1["x"].asInt();
	int d = monsterSpawnPoint1["y"].asInt();
	DemonPosition = Vec2(c, d);

	/*
	while (true) {
		int i = 0;
		char str[100];
		sprintf(str, "Monster");
	}
	*/

	this->createHero();
	this->createMonster(MonsterPosition);
	this->createDemon(DemonPosition);
	schedule(schedule_selector(HelloWorld::StageCheck),0.2f);
    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
void HelloWorld::createHero() {

	Vector<SpriteFrame*> aniFrames;

	char str[100] = { 0 };
	for (int i = 1; i < 4; i++) {
		sprintf(str, "Hero%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		aniFrames.pushBack(frame);
	}

	Hero = Sprite::createWithSpriteFrameName("Hero01.png");
	Hero->setPosition(HeroPosition);
	this->addChild(Hero, 1);

	auto animation = Animation::createWithSpriteFrames(aniFrames, 0.5f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	Hero->runAction(rep);
}
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	return true;
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = Hero->getPosition();
	Vec2 diff = touchPoint - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += tmap->getTileSize().width;
			Hero->setFlippedX(true);
		}
		else {
			playerPos.x -= tmap->getTileSize().width;
			Hero->setFlippedX(false);
		}

	}
	else {
		if (diff.y > 0) {
			playerPos.y += tmap->getTileSize().height;
		}
		else {
			playerPos.y -= tmap->getTileSize().height;
		}
	}

	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width) &&
		playerPos.y <= (tmap->getMapSize().height * tmap->getTileSize().height) &&
		playerPos.x >= 0 &&
		playerPos.x >= 0) {
		this->setPlayerPosition(playerPos);
	}
	this->setViewpointCenter(Hero->getPosition());
}
void HelloWorld::setViewpointCenter(Vec2 position) {
	int x = MAX(position.x, (winSize.width / 2));
	int y = MAX(position.y, (winSize.height / 2));

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - (winSize.width / 2));
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - (winSize.height / 2));

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}
Vec2 HelloWorld::tileCoordForPosition(Vec2 position) {
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;

	return Vec2(x, y);
}
void HelloWorld::setPlayerPosition(Vec2 position) {
	Vec2 tileCoord = this->tileCoordForPosition(position);  //position의 타일코드번호를 가져온다

	int tileGid = this->metainfo->getTileGIDAt(tileCoord);  //metainfo레이어에 타일코드번호의 아이디를 가져온다

	if (tileGid) {
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string monster = properties.asValueMap()["Monster"].asString();
			if (monster == "mon") {
				if (ps == SWORD) {
					this->metainfo->removeTileAt(tileCoord);
					items->removeTileAt(tileCoord);
					this->removeChild(Monster);
					ps = IDLE;
				}
				else {
					log("mon");
					return;
				}
			}
			else if (monster == "jelly") {
				if (ps == ROAD) {
					this->metainfo->removeTileAt(tileCoord);
					items->removeTileAt(tileCoord);
					ps = IDLE;
				}
				else {
					log("jelly");
					return;
				}
			}
			else if (monster == "demon") {
				if (ps == HOLY) {
					this->metainfo->removeTileAt(tileCoord);
					items->removeTileAt(tileCoord);
					this->removeChild(Demon);
					ps = IDLE;
				}
				else {
					log("demon");
					return;
				}
			}
			else if (monster == "box") {
				if (ps == KEY) {
					this->metainfo->removeTileAt(tileCoord);
					items->removeTileAt(tileCoord);
					bClear = true;
					ps = IDLE;
				}
				else {
					log("box");
					return;
				}
			}
			std::string itemss = properties.asValueMap()["Items"].asString();
			if (itemss == "sword") {
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("sword");
				Hero->setPosition(position);
				ps = SWORD;
			}
			else if (itemss == "road") {
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("road");
				Hero->setPosition(position);
				ps = ROAD;
			}
			else if (itemss == "holy") {
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("holy");
				Hero->setPosition(position);
				ps = HOLY;
			}
			else if (itemss == "key") {
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);
				log("key");
				ps = KEY;
			}
		}
	}
	Hero->setPosition(position);
}
void HelloWorld::StageCheck(float t) {
	if (bClear && stage == 1) {
		log("%d,   %d", Hero->getPosition().x, Hero->getPosition().y);
		this->removeChild(tmap);
		log("delete tmpa");
		tmap = TMXTiledMap::create("stage2.tmx");
		background = tmap->getLayer("Background");
		items = tmap->getLayer("Items");
		metainfo = tmap->getLayer("MetaInfo");
		metainfo->setVisible(false);

		this->addChild(tmap, 0, 11);

		objects = tmap->getObjectGroup("Object");
		ValueMap spawnPoint = objects->getObject("SpawnPoint");

		int x = spawnPoint["x"].asInt();
		int y = spawnPoint["y"].asInt();
		log("%d,   %d", x, y);
		this->removeChild(Hero);
		HeroPosition = Vec2(x, y); // 80 240
		createHero();
		log("create Hero");
		bClear = false;
		stage++;
	}
	else if (bClear && stage == 2) {
		log("%d,   %d", Hero->getPosition().x, Hero->getPosition().y);
		this->removeChild(tmap);
		log("delete tmpa");
		tmap = TMXTiledMap::create("stage3.tmx");
		background = tmap->getLayer("Background");
		items = tmap->getLayer("Items");
		metainfo = tmap->getLayer("MetaInfo");
		metainfo->setVisible(false);

		this->addChild(tmap, 0, 11);

		objects = tmap->getObjectGroup("Object");
		ValueMap spawnPoint = objects->getObject("SpawnPoint");

		int x = spawnPoint["x"].asInt();
		int y = spawnPoint["y"].asInt();
		log("%d,   %d", x, y);
		this->removeChild(Hero);
		HeroPosition = Vec2(x, y); // 80 240
		createHero();
		log("create Hero");
		bClear = false;
	}
}
void HelloWorld::createDemon(Vec2 spawn) {

	Vector<SpriteFrame*> monFrames;
	char str[100] = { 0 };
	for (int i = 1; i < 4; i++) {
		sprintf(str, "Demon%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monFrames.pushBack(frame);
	}
	Demon = Sprite::createWithSpriteFrameName("Demon1.png");
	Demon->setPosition(spawn);
	this->addChild(Demon, 1);

	auto animation = Animation::createWithSpriteFrames(monFrames, 0.5f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	Demon->runAction(rep);
}
void HelloWorld::createMonster(Vec2 spawn) {

	Vector<SpriteFrame*> monFrames;

	char str[100] = { 0 };
	for (int i = 1; i < 4; i++) {
		sprintf(str, "Wolf%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		monFrames.pushBack(frame);
	}

	Monster = Sprite::createWithSpriteFrameName("Wolf1.png");
	Monster->setPosition(spawn);
	this->addChild(Monster, 1);

	auto animation = Animation::createWithSpriteFrames(monFrames, 0.5f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);

	Monster->runAction(rep);
}