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

	map = TMXTiledMap::create("TileMap/iso-test-touch.tmx");
	this->addChild(map, 0, 1);
	Size s = map->getContentSize();
	log("content Size : %f   %f", s.width, s.height);
	map->setPosition(Vec2(0, 0));

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
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();
	touchPoint = map->convertToNodeSpace(touchPoint);
	Vec2 pos = touchToXY(touchPoint, 10);
	log("gid.x = %f,  gid.y = %f",
		pos.x,
		pos.y);
	return true;
}
Vec2 HelloWorld::touchToXY(Vec2 touch, int mapsize) {
	Size ts = map->getTileSize();
	int isoy = (((touch.y / ts.height) + (touch.x - (mapsize * ts.width / 2)) / ts.width) - mapsize) *-1;
	int isox = (((touch.y / ts.height) - (touch.x - (mapsize * ts.width / 2)) / ts.width) - mapsize) *-1;
	return Vec2(isox, isoy);
}