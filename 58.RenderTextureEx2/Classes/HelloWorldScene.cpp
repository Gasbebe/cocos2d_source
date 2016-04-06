﻿#include "HelloWorldScene.h"

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
	winSize = Director::getInstance()->getWinSize();

	//텍스쳐사이즈 조절
	m_pTarget = RenderTexture::create(winSize.width/2,
		winSize.height/2,
		Texture2D::PixelFormat::RGBA8888);

	m_pTarget->retain();
	m_pTarget->setPosition(Vec2(winSize.width/2, winSize.height/2));
	this->addChild(m_pTarget, 1);

	MenuItemFont::setFontSize(16);
	auto item1 = MenuItemFont::create("save image", CC_CALLBACK_1(HelloWorld::saveImage, this));
	item1->setColor(Color3B::BLACK);

	auto item2 = MenuItemFont::create("clear", CC_CALLBACK_1(HelloWorld::clearImage, this));
	item2->setColor(Color3B::BLACK);

	auto menu = Menu::create(item1, item2, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(winSize.width - 80, winSize.height - 30));
	this->addChild(menu, 3);

	TableView* tableView1 = TableView::create(this, Size(250, 250));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2(120, 0));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	this->addChild(tableView1);
	tableView1->reloadData();

	auto layer2 = Layer::create();
	layer2->setScale(0.5);
	this->addChild(layer2,2);

	bg = Sprite::create("Images/image01.png");
	bg->setPosition(Vec2(240, 160));
	this->addChild(bg,3);
    return true;
}

HelloWorld::~HelloWorld() {
	m_pTarget->release();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void HelloWorld::onEnter() {

	Layer::onEnter();
	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event* event) {
	auto touch = touches[0];
	Vec2 start = touch->getLocation();
	Vec2 end = touch->getPreviousLocation();

	// begin 과 end 사이 있는것을 저장
	m_pTarget->begin();

	float distance = start.getDistance(end);
	if (distance > 1) {
		int d = (int)distance;
		m_pBrush.clear();

		for (int i = 0; i < d; ++i) {
			Sprite* sprite = Sprite::create("Images/brush2.png");
			sprite->setColor(Color3B::GREEN);
			//sprite->setOpacity(20);
			//sprite->setOpacity(150);
			m_pBrush.pushBack(sprite);
		}
		for (int i = 0; i < d; i++) {

			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;

			m_pBrush.at(i)->setPosition(Vec2(start.x + (difx*delta)-120, start.y + (dify* delta)-100));
			m_pBrush.at(i)->setRotation(rand() % 360);

			float r = (float)(rand() % 50 / 50.f) + 0.25f;
			m_pBrush.at(i)->setScale(r);
			m_pBrush.at(i)->visit();
		}
	}
	m_pTarget->end();
}

void HelloWorld::saveImage(Ref* sender) {

	static int counter = 0;
	char png[20];
	sprintf(png, "image-%d.png", counter);


	//Type 2

	m_pTarget->saveToFile(png, Image::Format::PNG, true, nullptr);

	//화면 캡쳐부분 밑에하단에 보여줌
	auto image = m_pTarget->newImage();
	auto tex = Director::getInstance()->getTextureCache()->addImage(image, png);

	CC_SAFE_DELETE(image);

	auto sprite = Sprite::createWithTexture(tex);

	sprite->setScale(0.3f);
	sprite->setPosition(Vec2(40, 40));
	sprite->setRotation(counter * 3);

	addChild(sprite);

	Director::getInstance()->getRenderer()->render();
	log("Image saved %s", png);

	counter++;
}

void HelloWorld::clearImage(Ref* sender) {

	m_pTarget->clear(255, 255, 255, 255);

}

/////////////////////////////////////////////////////////////////////////

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell) {
	log("Tag : %d\nCell touched at index : %ld",
		table->getTag(),
		cell->getIdx());
}

Size HelloWorld::tableCellSizeForIndex(TableView* table, ssize_t idx) {
	if (idx == 2) {
		return Size(90, 90);
	}
	return Size(90, 90);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView *table, ssize_t idx) {

	auto string = String::createWithFormat("%ld", idx);
	char str[30];
	
	TableViewCell *cell = table->dequeueCell();

	//cell이 없으면 만든다
	if (!cell) {
		sprintf(str, "Images/crayon_%02d.png", count);
		cell = new CustomTableViewCell();
		cell->autorelease();
		auto sprite = Sprite::create(str);
		sprite->setPosition(Vec2(0, 0));
		cell->addChild(sprite);
		
		auto label = LabelTTF::create(string->getCString(), "Helvetica", 20.0);
		label->setColor(Color3B::BLACK);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		cell->addChild(label);
		
		count++;
	}
	//있으면 있는걸 쓴다
	else {
		auto label = (LabelTTF*)cell->getChildByTag(123);
		label->setString(string->getCString());
		count++;
	}
	if (count > 13) {
		count = 0;
	}
	
	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView* table) {
	return 13;
}