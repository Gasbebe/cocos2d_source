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
	//스프라이트 텍스쳐를 만들어 수동으로 파일을 구분하는것이아니고
	//미리 지정한  정보파일을 이용해 파일을 구분한다

	//스프라이트 시트의 위치정보 파일을 읽어들인다
	//같은 디렉터리 위치에 plist와 같은 이름의 png가 있어야한다

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("animations/grossini.plist");

	Vector<SpriteFrame*> animFrames;
	char str[100] = { 0 };

	for (int i = 1; i < 15; i++) {
		sprintf(str, "grossini_dance_%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	//스프라이트 생성
	auto pMan = Sprite::createWithSpriteFrameName("grossini_dance_01.png"); //vector의 처음으로 들어간 데이터
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	//애니메이셔만들기
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f); //vector형에 데이터를 받아오고 시간지정
	auto animate = Animate::create(animation);

	auto rep = RepeatForever::create(animate);

	pMan->runAction(rep);

    return true;
}
