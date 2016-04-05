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
	auto texture = Director::getInstance()->getTextureCache()->addImage("puzzle.png");
	auto sprite = Sprite::create("puzzle.png");
	sprite->setScale(0.4);
	sprite->setPosition(350, 240);
	this->addChild(sprite);
	size = Director::getInstance()->getWinSize();

	for (int i = 0; i < 8; i++) {
		int x = i%3;
		int row = i/3;
		//position

		sildePuzzle[i] = Sprite::createWithTexture(texture, Rect(x*76, row*76, 76, 76));
		sildePuzzle[i]->setPosition(Vec2((x*78)+100, (2-row)*78+100));
		sildePuzzle[i]->setTag(i);
		puzzlePosition[i] = sildePuzzle[i]->getPosition();
		this->addChild(sildePuzzle[i]);
	}
	puzzlePosition[8] = Vec2(256,100);
	for (int i = 7; i >=0; i--) {

	}
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	initSuffle();
	//this->schedule(schedule_selector(HelloWorld::CheckNullPosition));
    return true;
}



bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	auto touchPoint = touch->getLocation();

	log("onTouchBegan id =%d, x = %f, y = %f",
		touch->getID(),
		touchPoint.x,
		touchPoint.y);

	for (int i = 0; i < 8; i++) {
		bool bTouch = sildePuzzle[i]->getBoundingBox().containsPoint(touchPoint);
		if (bTouch) {
			int tagNum = sildePuzzle[i]->getTag();
			SwapPosition(tagNum, i);
			log("sprite touch %d",i);
			log("null Position %d", nullPosition);
			log("%d", sildePuzzle[i]->getTag());
		}
	}
	return true;
}

void HelloWorld::CheckNullPosition() {
	while(true){
		int tagNum = sildePuzzle[count]->getTag();
		if (count == tagNum) {
			count++;
			if (count == 7) {
				log("clear");
				count = 0;
				break;
			}
		}
		else {
			break;
			return;
		}
	}

}
void HelloWorld::SwapPosition(int i, int puzzleNum) {
	//스프라이트 태그로 비어있는 위치를 찾아서 스프라이트의 태그 교환 및 위치 교환
	if (nullPosition - 1 == i && nullPosition != 3 && nullPosition != 6) {
		sildePuzzle[puzzleNum]->setPosition(puzzlePosition[nullPosition]);
		sildePuzzle[puzzleNum]->setTag(nullPosition);
		temp = i;
		i = nullPosition;
		nullPosition = temp;
	}
	else if (nullPosition + 1 == i && nullPosition != 2 && nullPosition !=5) {

		sildePuzzle[puzzleNum]->setPosition(puzzlePosition[nullPosition]);
		sildePuzzle[puzzleNum]->setTag(nullPosition);
		temp = i;
		i = nullPosition;
		nullPosition = temp;
	}
	else if (nullPosition + 3 == i) {
		sildePuzzle[puzzleNum]->setPosition(puzzlePosition[nullPosition]);
		sildePuzzle[puzzleNum]->setTag(nullPosition);
		temp = i;
		i = nullPosition;
		nullPosition = temp;
	}
	else if (nullPosition - 3 == i) {
		sildePuzzle[puzzleNum]->setPosition(puzzlePosition[nullPosition]);
		sildePuzzle[puzzleNum]->setTag(nullPosition);
		temp = i;
		i = nullPosition;
		nullPosition = temp;
	}
	CheckNullPosition();
}
void HelloWorld::initSuffle() {
	Vec2 randVec[9] = { puzzlePosition[8],puzzlePosition[0], puzzlePosition[1],puzzlePosition[2],puzzlePosition[3],
		puzzlePosition[4],puzzlePosition[5],puzzlePosition[6],puzzlePosition[7] };
	Vec2 emptyCoord;
	int n = 0;
	srand((int)time(NULL));

	while (n < 5000) {
		n++;
		auto randTouch = emptyCoord + randVec[rand() % 8];
		log("%d (%f, %f)", n, randTouch.x, randTouch.y);

		for (int i = 0; i < 8; i++) {
			if (sildePuzzle[i]->getBoundingBox().containsPoint(randTouch)) {
				int tagNum = sildePuzzle[i]->getTag();
				SwapPosition(tagNum, i);
			}
		}
	}
}

