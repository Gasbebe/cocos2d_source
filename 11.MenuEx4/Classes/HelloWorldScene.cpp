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
	//메뉴아이템 생성 초기화
	auto pMenuItem1 = MenuItemFont::create("Menu-1", CC_CALLBACK_1(HelloWorld::doClick, this));
	auto pMenuItem2 = MenuItemFont::create("Menu-2", CC_CALLBACK_1(HelloWorld::doClick, this));
	pMenuItem1->setColor(Color3B::BLACK);
	pMenuItem2->setColor(Color3B::BLACK);
	//태그번호 설정
	pMenuItem1->setTag(1);
	pMenuItem2->setTag(2);
	
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->alignItemsVertically();
	this->addChild(pMenu);

    return true;
}

void HelloWorld::doClick(Ref* pSender) {
	auto tItem = (MenuItem*)pSender;
	int i = tItem->getTag();

	if (i == 1) { //1번 메뉴가 눌림
		auto pMan = Sprite::create("Images/grossini.png");

		pMan->setPosition(Vec2(100, 100));
		pMan->setTag(11);

		this->addChild(pMan);
	}
	else {
		auto pMan = (Sprite*)getChildByTag(11);  //태그가 11번인 스프라이트 자식을 가져와서 지움
		//pMan의  자식을 지우는데 PMan스프라이트제거
		this->removeChild(pMan, true);
	}
	
}//flip