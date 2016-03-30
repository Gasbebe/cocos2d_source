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
	//백그라운드
	bg = Sprite::create("Background/Background.png");
	bg->setPosition(Vec2(320, 480));
	this->addChild(bg);

	//물고기 스프라이트
	fish1 = Sprite::create("Fish_Effect/Fish_001.png");
	fish1->setPosition(Vec2(0, 450));
	this->addChild(fish1);

	fish2 = Sprite::create("Fish_Effect/Fish_002.png");
	fish2->setPosition(Vec2(640, 400));
	this->addChild(fish2);

	fish3 = Sprite::create("Fish_Effect/Fish_001.png");
	fish3->setPosition(Vec2(-20, 200));
	this->addChild(fish3);

	//버블 스프라이트
	bubble = Sprite::create("Bubble_Effect/Title_Bubble_001.png");
	bubble->setPosition(Vec2(320, -20));
	this->addChild(bubble);

	bubble2 = Sprite::create("Bubble_Effect/Title_Bubble_002.png");
	bubble2->setPosition(Vec2(320, -20));
	this->addChild(bubble2);

	bubble3 = Sprite::create("Bubble_Effect/Title_Bubble_003.png");
	bubble3->setPosition(Vec2(320, -20));
	this->addChild(bubble3);

	bubble4 = Sprite::create("Bubble_Effect/Title_Bubble_004.png");
	bubble4->setPosition(Vec2(320, -20));
	this->addChild(bubble4);

	bubbleStar = Sprite::create("Bubble_Effect/Bubble_Star_003.png");
	bubbleStar->setPosition(Vec2(320, 50));
	bubbleStar->setScale(0.5f);
	this->addChild(bubbleStar);

	bubbleStar2 = Sprite::create("Bubble_Effect/Bubble_Star_002.png");
	bubbleStar2->setPosition(Vec2(100, 100));
	bubbleStar2->setScale(0.2f);
	this->addChild(bubbleStar2);

	bubbleStar3 = Sprite::create("Bubble_Effect/Bubble_Star.png");
	bubbleStar3->setPosition(Vec2(600, 100));
	bubbleStar3->setScale(0.3f);
	this->addChild(bubbleStar3);


	//버튼 스프라이트
	////////////////////////////////////
	auto pMenuItem1 = MenuItemImage::create(
		"Create_Button/Play_Button_01.png",
		"Create_Button/Play_Button_02.png");
	pMenuItem1->setPosition(Vec2(290, 300));

	auto pMenuItem2 = MenuItemImage::create(
		"Create_Button/Vibration_ON.png",
		"Create_Button/Vibration_OFF.png");
	pMenuItem2->setPosition(Vec2(420, 180));

	auto pMenuIteme3 = MenuItemImage::create(
		"Create_Button/Create_Button_01.png",
		"Create_Button/Create_Button_02.png");
	pMenuIteme3->setPosition(Vec2(600, 50));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuIteme3, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu);
	////////////////////////////////////
	
	//buttonStart = Sprite::create("Create_Button/Play_Button_01.png");
	//buttonStart->setPosition(Vec2(290, 300));
	//this->addChild(buttonStart);

	//buttonInfo = Sprite::create("Create_Button/Vibration_ON.png");
	//buttonInfo->setPosition(Vec2(420, 180));
	//this->addChild(buttonInfo);

	buttonFx = Sprite::create("Create_Button/Base.png");
	buttonFx->setPosition(Vec2(320, 280));
	buttonFx->setOpacity(0);
	this->addChild(buttonFx);
	

	logo = Sprite::create("Create_Button/Bubble_Logo.png");
	logo->setPosition(Vec2(320, 680));
	this->addChild(logo);
	
	//buttonEx = Sprite::create("Create_Button/Create_Button_01.png");
	//buttonEx->setPosition(Vec2(600, 50));
	//this->addChild(buttonEx);
	
	buttonExBase = Sprite::create("Create_Button/Create_base.png");
	buttonExBase->setPosition(Vec2(600, 50));
	buttonExBase->setScale(1.1f);
	this->addChild(buttonExBase);

	//빛 스프라이트
	topLite = Sprite::create("Bubble_Effect/Lighting_Background.png");
	topLite->setPosition(Vec2(320,800));
	this->addChild(topLite);

	leftLite = Sprite::create("Bubble_Effect/Title_Light_Effect.png");
	leftLite->setPosition(Vec2(280, 600));
	leftLite->setScale(1.5f);
	this->addChild(leftLite);

	bgLite = Sprite::create("Bubble_Effect/Flash_001.png");
	bgLite->setPosition(Vec2(280, 600));
	this->addChild(bgLite);

	bgLite2 = Sprite::create("Bubble_Effect/Flash_002.png");
	bgLite2->setPosition(Vec2(280, 600));
	this->addChild(bgLite2);

	bgLite3 = Sprite::create("Bubble_Effect/Flash_003.png");
	bgLite3->setPosition(Vec2(280, 600));
	this->addChild(bgLite3);

	//액션실행함수
	BubbleAction();
	LogoAction();
	ButtonAction();
	LiteAction();
	FishAction();
    return true;
}
void HelloWorld::BubbleAction() {
	auto move = MoveBy::create(1, Vec2(0,1500));
	auto move2 = MoveBy::create(2, Vec2(0, 1500));
	auto move3 = MoveBy::create(3, Vec2(0, 1500));
	auto move4 = MoveBy::create(4, Vec2(0, 1500));

	auto bublePos = Place::create(Vec2(320, 0));
	
	auto rotAction = RotateBy::create(2, 180);

	//auto move4 = Speed::create(move->clone(), 1.5f);
	
	auto bubleM = Sequence::create(move->clone(), bublePos, nullptr);
	auto bubleM2 = Sequence::create(move2->clone(), bublePos, nullptr);
	auto bubleM3 = Sequence::create(move3->clone(), bublePos, nullptr);
	auto bubleM4 = Sequence::create(move4->clone(), bublePos, nullptr);

	//auto bubleM4 = Sequence::create(move4, bublePos, nullptr);

	auto rep = RepeatForever::create(bubleM);
	auto rep2 = RepeatForever::create(bubleM2);
	auto rep3 = RepeatForever::create(bubleM3);
	auto rep4 = RepeatForever::create(bubleM4);
	auto rep5 = RepeatForever::create(rotAction);

	bubble->runAction(rep);
	bubble2->runAction(rep2);
	bubble3->runAction(rep3);
	bubble4->runAction(rep4);
	bubbleStar->runAction(rep5->clone());
	bubbleStar2->runAction(rep5->clone());
	bubbleStar3->runAction(rep5->clone());

}
void HelloWorld::LogoAction() {

	auto move = MoveBy::create(1, Vec2(0, 20));
	auto moveR = move->reverse();

	auto logoM = Sequence::create(move->clone(), moveR, nullptr);
	auto rep = RepeatForever::create(logoM);

	logo->runAction(rep);
}

void HelloWorld::ButtonAction() {
	auto action = FadeIn::create(1.0f);
	auto action2 = FadeOut::create(1.0f);

	auto action3 = RotateBy::create(2, 180);

	auto buttomA = Sequence::create(action->clone(), action2->clone(), nullptr);
	auto rep = RepeatForever::create(buttomA);
	auto rep2 = RepeatForever::create(action3);

	buttonFx->runAction(rep);
	buttonExBase->runAction(rep2);
}

void HelloWorld::FishAction() {

	auto move = MoveBy::create(5, Vec2(640, 0));
	auto move2 = MoveBy::create(10, Vec2(-640, 0));
	auto move3 = MoveBy::create(10, Vec2(640, 0));

	auto FishPos = Place::create(Vec2(0, 480));
	auto FishPos2 = Place::create(Vec2(640, 400));
	auto FishPos3 = Place::create(Vec2(-20, 200));

	//auto move4 = Speed::create(move->clone(), 1.5f);

	auto fishM = Sequence::create(move->clone(), FishPos, nullptr);
	auto fishM2 = Sequence::create(move2->clone(), FishPos2, nullptr);
	auto fishM3 = Sequence::create(move3->clone(), FishPos3, nullptr);

	//auto bubleM4 = Sequence::create(move4, bublePos, nullptr);

	auto rep = RepeatForever::create(fishM);
	auto rep2 = RepeatForever::create(fishM2);
	auto rep3 = RepeatForever::create(fishM3);

	fish1->runAction(rep);
	fish2->runAction(rep2->clone());
	fish3->runAction(rep3->clone());
}
void HelloWorld::LiteAction() {
	auto action = FadeIn::create(1.0f);
	auto action2 = FadeOut::create(1.0f);
	auto action3 = FadeIn::create(2.0f);
	auto action4 = FadeOut::create(2.0f);

	auto flash = Sequence::create(action3->clone(), action4->clone() , nullptr);
	auto flash2 = Sequence::create(action->clone(), action4->clone(), nullptr);
	auto flash3 = Sequence::create(action3->clone(), action2->clone(), nullptr);
	auto flash4 = Sequence::create(action->clone(), action2->clone(), nullptr);

	auto rep = RepeatForever::create(flash);
	auto rep2 = RepeatForever::create(flash2);
	auto rep3 = RepeatForever::create(flash3);
	auto rep4 = RepeatForever::create(flash4);

	topLite->runAction(rep->clone());
	leftLite->runAction(rep->clone());

	bgLite->runAction(rep2->clone());
	bgLite2->runAction(rep3->clone());
	bgLite3->runAction(rep4->clone());
}