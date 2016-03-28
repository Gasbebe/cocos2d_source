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
	pMenuItem->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem, nullptr);
	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	this->addChild(pMan);

    return true;
}

//액션을 부를곳을 정하는 함수
void HelloWorld::doAction(Ref* pSender) {

	pMan->removeAllChildrenWithCleanup(true);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 150));
	this->addChild(pMan);
	
	//부를함수 바꾸는곳
	this->ActionSequence(this);
}

void HelloWorld::ActionSequence(Ref* pSender) {
	auto action = Sequence::create(MoveBy::create(2, Vec2(400, 0)),
		RotateBy::create(2, 40), nullptr);

	pMan->runAction(action);
}

void HelloWorld::ActionSpwan(Ref* pSender) {
	//4초에 4번 점프  회전은 2초만 동시에 실행
	//2초회전이 끝나도 4초동안 점프한다 액션시간은 긴시간에 맞쳐실행

	//배열데이터형 끝에는 널값이 들어가야함
	auto action = Spawn::create(JumpBy::create(4, Vec2(400, 0), 100, 3),
		RotateBy::create(2, 720), nullptr);

	pMan->runAction(action);
}

void HelloWorld::ActionReverse(Ref* pSender) {
	auto action = MoveBy::create(2, Vec2(400, 0));
	auto reverseAction = action->reverse();

	pMan->runAction(reverseAction);
}

void HelloWorld::ActionRepeat(Ref* pSender) {
	auto myActionForward = MoveBy::create(2, Vec2(400, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);

	auto rep1 = Repeat::create(myAction, 3);

	pMan->runAction(rep1);
}

void HelloWorld::ActionRepeatForever(Ref* pSender) {
	auto myActionForward = MoveBy::create(2, Vec2(400, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);

	auto rep2 = RepeatForever::create(myAction);

	pMan->runAction(rep2);
}

void HelloWorld::DelayTime(Ref* pSender) {
	auto act1 = RotateTo::create(1, 150);
	auto act2 = RotateTo::create(1, 0);

	auto myAction = Sequence::create(act1, DelayTime::create(2), act2, DelayTime::create(1), nullptr);

	auto rep2 = RepeatForever::create(myAction);

	pMan->runAction(rep2);
}















