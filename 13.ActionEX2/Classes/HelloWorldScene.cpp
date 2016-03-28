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
	MenuItemFont::setFontSize(28);

	auto pMenuItem = MenuItemFont::create(" Action ", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B(0, 0, 0));


	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->alignItemsHorizontally();
	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 200));
	this->addChild(pMan);

	return true;
}

void HelloWorld::doAction(Ref* pSender) {
	//auto myAction = MoveBy::create(2, Vec2(400, 0));//로컬좌표(케릭터) x축으로 400만큼 y로 0만큼가라
	//auto myAction = MoveTo::create(2, Vec2(400, 0));//전역좌표(화면) 400, 0으로 이동하여라
	//auto myAction = JumpBy::create(2, Vec2(400, 0), 50, 3); //점프3번만에 400, 0쪽으로간다
	//auto myAction = JumpTo::create(2, Vec2(400, 0), 50, 3); //400, 0 쪽으로간다
	//auto myAction = RotateTo::create(2, 90); //2초동안 90도로 가까운쪽 방향으로 회전
	//auto myAction = RotateBy::create(2, 90); //2초동안 90만큼 가까운쪽 방향으로 회전
	//auto myAction = Blink::create(2, 5);  //2초동안 5번 깜박임
	//auto myAction = TintTo::create(2, 128, 128, 128); //색깔이 확 어두워짐
	auto myAction = TintBy::create(2, 128, 128, 128);  //새깔이 점점 바뀜 의한

	//리버스 할때 By는 실행이 되고 To는 실행이안됨
	//To는 어디로 가라 위치를 지정하기때문에 각각 대응하는 거리가 각각달라 컴퓨터가 계산하기힘듬
	//By는 자신에 대해서 거리를 계산하기 떄문에 값이 나와 리버스 가능
	auto myActionBack = myAction->reverse();
	pMan->runAction(myActionBack);
}
