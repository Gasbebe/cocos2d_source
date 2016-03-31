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
	auto map = TMXTiledMap::create("TileMap/orthogonal-test-zorder.tmx");
	this->addChild(map, 0, 1);
	Size s = map->getContentSize();
	log("ContenSize : %f  %f , ",s.width, s.height);
	map->setPosition(Vec2(-s.width / 2, 0));
	
	m_tamara = Sprite::create("TileMap/grossinis_sister1.png");
	map->addChild(m_tamara, map->getChildren().size());
	int mapWidth = map->getMapSize().width * map->getTileSize().width;
	m_tamara->setPosition(CC_POINT_PIXELS_TO_POINTS(Vec2(mapWidth / 2, 0)));
	m_tamara->setAnchorPoint(Vec2(0.5f, 0));

	auto move = MoveBy::create(10, Vec2(400, 320));
	auto back = move->reverse();
	auto seq = Sequence::create(move, back, nullptr);
	m_tamara->runAction(RepeatForever::create(seq));
	
	this->schedule(schedule_selector(HelloWorld::repositionSprite));


    return true;
}

void HelloWorld::repositionSprite(float t) {

	Vec2 p = m_tamara->getPosition();
	p = CC_POINT_PIXELS_TO_POINTS(p);
	Node* map = getChildByTag(1);

	int newZ = 4 - (p.y / 48);
	newZ = MAX(newZ, 0);
	//케릭터를 zorder를 새로 정할려면 child로 받아와야함
	map->reorderChild(m_tamara, newZ);
}
