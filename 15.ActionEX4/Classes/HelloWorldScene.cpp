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
	auto pMenuItem = MenuItemFont::create("Action", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));
	this->addChild(pMenu);

	pBall = Sprite::create("Images/r1.png");
	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);
	this->addChild(pBall);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);
	this->addChild(pMan);

	pWomen1 = Sprite::create("Images/grossinis_sister1.png");
	pWomen1->setPosition(Vec2(50, 220));
	pWomen1->setScale(0.5f);
	this->addChild(pWomen1);

	pWomen2 = Sprite::create("Images/grossinis_sister2.png");
	pWomen2->setPosition(Vec2(50, 280));
	pWomen2->setScale(0.5f);
	this->addChild(pWomen2);

    return true;
}

void HelloWorld::doAction(Ref* pSender) {
	doActionReset();

	auto move = MoveBy::create(3.0f, Vec2(400, 0));

	//속도------------------------------------------
	//시작이 늦고 나중에 빠름
	auto ease_in = EaseIn::create(move->clone(), 4.0f);
	//느려지기 : 시작이빠르고 나중이 느림
	auto ease_out = EaseOut::create(move->clone(), 4.0f);
	//빨라졌다 느려짐 : 시작과 끝이빠름
	auto ease_inout1 = EaseInOut::create(move->clone(), 4.0f);

	//탄성 ---------------------------------------------
	//시작 부분 탄성
	//auto ease_in = EaseElasticIn::create(move->clone(), 4.0f);
	//끝 부분 탄성
	//auto ease_out = EaseElasticOut::create(move->clone(), 4.0f);
	//시작 부분과 끝 부분탄성
	//auto ease_inout1 = EaseElasticInOut::create(move->clone(), 4.0f);
	
	//바운스--------------------------------------------------------------
	//auto ease_in = EaseBounceIn::create(move->clone());  //시작부분 바운스
	//auto ease_out = EaseBounceOut::create(move->clone()); //끝부분 바운스
	//auto ease_inout1 = EaseBounceInOut::create(move->clone()); //시작 끝부분 바운스
	
	//스피드 조정
	//auto ease_in = Speed::create(move->clone(), 4.0f);
	//auto ease_out = Speed::create(move->clone(), 1.5f);
	//auto ease_inout1 = Speed::create(move->clone(), 1.0f);

	pBall->runAction(move);
	pMan->runAction(ease_in);
	pWomen1->runAction(ease_out);
	pWomen2->runAction(ease_inout1);
}
void HelloWorld::doActionReset() {

	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);

	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);

	pWomen1->setPosition(Vec2(50, 220));
	pWomen1->setScale(0.5f);

	pWomen2->setPosition(Vec2(50, 280));
	pWomen2->setScale(0.5f);

}