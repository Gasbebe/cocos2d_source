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
	pMenuItem->setColor(Color3B(0,0,0));

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
	//auto myAction = JumpBy::create(2, Vec2(400, 0), 50, 3); 점프3번만에 400, 0쪽으로간다
	//auto myAction = JumpTo::create(2, Vec2(400, 0), 50, 3); 400, 0 쪽으로간다
	//auto myAction = RotateTo::create(2, 90); //2초동안 90도로 가까운쪽 방향으로 회전
	//auto myAction = RotateBy::create(2, 90); //2초동안 90만큼 가까운쪽 방향으로 회전
	//auto myAction = Blink::create(2, 5);  //2초동안 5번 깜박임
	//auto myAction = TintTo::create(2, 128, 128, 128); //색깔이 어두워짐
	auto myAction = TintBy::create(2, 128, 128, 128);  //검은색으로 됐다가 원래대로 점점 돌아옴

	pMan->runAction(myAction);
}
