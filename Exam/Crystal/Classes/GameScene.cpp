#include "GameScene.h"

USING_NS_CC;

std::vector<int> gBoard;
std::vector<cocos2d::Sprite*> gBoardSprites;
std::vector<int> gNumGemsInColumn; //8
std::vector<int> gTimeSinceAddInColumn; //8

int gameTime = 100;
int kGemSize = 40;
int kBoardWidth = 8;
int kBoardHeight = 10;
int kNumTotalGems = kBoardWidth * kBoardHeight;
int kTimeBetweenGemAdds = 8;
int kTotalGameTime = 1000 * 60;
int kIntroTime = 1800;
int kNumRemovalFrames = 8;
int kDelayBeforeHint = 3000;
int kMaxTimeBetweenConsecutiveMoves = 1000;
int kGameOverGemSpeed = 0.1;
int kGameOverGemAcceleration = 0.005;


Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto Gamelayer = GameScene::create();
	scene->addChild(Gamelayer);

	// return the scene
	return scene;
}

bool GameScene::init()
{

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////
	winSize = Director::getInstance()->getWinSize();
	//Layer create
	gGameLayer = Layer::create();
	addChild(gGameLayer);

	gParticleLayer = Layer::create();
	addChild(gParticleLayer);

	gHintLayer = Layer::create();
	addChild(gHintLayer);

	gShimmerLayer = Layer::create();
	addChild(gShimmerLayer);

	gEffectsLayer = Layer::create();
	addChild(gEffectsLayer);
	//touch Listener

	//auto listener = EventListenerTouchOneByOne::create();



	
	//BackGround create

	auto bg = Sprite::create("Images/background.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	gGameLayer->addChild(bg);

	//this->schedule(schedule_selector(GameScene::fallingGem));

	header = Sprite::create("Images/header.png");
	header->setScale(0.8);
	header->setPosition(Vec2(winSize.width / 2, winSize.height - 30));
	gEffectsLayer->addChild(header);

	timeBar = Sprite::create("Images/timer.png");
	timeBar->setScale(0.8);
	timeBar->setAnchorPoint(Vec2(0,0.5));
	timeBar->setPosition(Vec2(0, winSize.height-60+1));
	gEffectsLayer->addChild(timeBar);

	//Box2D
	this->schedule(schedule_selector(GameScene::checkTime), 1.0f);
	fallingGem(1.0f);
			
	return true;
}

void GameScene::setupBoard() {
	gBoard; //80

	for (int i = 0; i < kNumTotalGems; i++) {
		gBoard.push_back(-1);
	}

	std::vector<cocos2d::Sprite*> gBoardSprites;
	std::vector<int> gNumGemsInColumn; //8
	std::vector<int> gTimeSinceAddInColumn; //8

	int x;

	for (x = 0; x < kBoardWidth; x++) {
		gNumGemsInColumn.at(x) = 0;
		gTimeSinceAddInColumn.at(x) = 0;
	}

	std::vector<cocos2d::Sprite*> gFallingGems;

	for (x = 0; x < kBoardWidth; x++) {
		gFallingGems.at(x) = 0;
	}
}

//�� ������ �κ�
void GameScene::fallingGem(float t) {
	if (true) {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 8; x++) {
				//60 60
				int nNum = rand() % 5;
				char crystalTyp[100];
				sprintf(crystalTyp, "Images/%d.png", nNum);
				texture = Director::getInstance()->getTextureCache()->addImage(crystalTyp);
				auto sprite = Sprite::create(crystalTyp);
				float xPos =(x % 8) * winSize.width / 8 + 30;
				float yPos = (y % 10)* winSize.height / 10 + 32 ;
				auto pos = Vec2(xPos, yPos);
				sprite->setScale(0.7);
				sprite->setPosition(pos);
				gGameLayer->addChild(sprite);

				//gem1 = new Gem();
				//gem1->setTexture(texture);
				//gem1->setPosition(pos);
				//gem1->SetPos(pos);
				//gem1->SetSize(texture->getContentSize());
				//gGameLayer->addChild(gem1);
				//addNewSpriteAtPosition(Vec2(xPos, yPos));
				/*
				b2BodyDef bodyDef;
				bodyDef.type = b2_dynamicBody;
				bodyDef.position.Set(xPos / PTM_RATIO, yPos / PTM_RATIO);
				//���������Ϳ� ��������Ʈ�� ���δ�
				bodyDef.userData = sprite;
				b2Body* body = _world->CreateBody(&bodyDef);


				// �ڽ� ����� ��ü ����
				
				b2PolygonShape dynamicBox;
				dynamicBox.SetAsBox((sprite->getContentSize().width / 2) / PTM_RATIO,
					(sprite->getContentSize().height / 2) / PTM_RATIO);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &dynamicBox;
				fixtureDef.density = 2.0f;
				fixtureDef.friction = 0.2f;
				fixtureDef.restitution = 0.1f;
				body->CreateFixture(&fixtureDef);
				*/
			}
		}		
	}
}

void GameScene::removeMarkedGems() {
	for (int x = 0; x < kBoardWidth; x++) {
		for (int y = 0; y < kBoardHeight; y++) {
			int i = x + y*kBoardWidth;

			if (gBoard.at(i) < -1) {
				gBoard.at(i)++;
				if (gBoard.at(i) == -1) {
					gNumGemsInColumn.at(x)--;
					//gBoardChangeSinceEvalution = true;
					for (int yAbove = y + 1; yAbove < kBoardHeight; yAbove++) {
						int idxAbove = x + yAbove*kBoardWidth;

						if (gBoard[idxAbove] < -1) {
							gNumGemsInColumn.at(x)--;
							gBoard.at(idxAbove) = -1;
						}
						if (gBoard.at(idxAbove) == -1) continue;

						int gemType = gBoard.at(idxAbove);
						auto gemSprite = gBoardSprites.at(idxAbove);
					
					}
					
				}
			}
		}
	}
}
void GameScene::findConnectedGems_(int x, int y, std::vector<int> arr, int gemType) {
	//check for bounds
	if (x < 0 || x >= kBoardWidth) return;
	if (y < 0 || y >= kBoardHeight) return;

	int idx = x + y*kBoardWidth;

	if (gBoard[idx] != gemType) return;

	for (int i = 0; i < arr.max_size(); i++) {
		if (arr.at(i) == idx) return;
	}
	arr.push_back(idx);

	findConnectedGems_(x + 1, y, arr, gemType);
	findConnectedGems_(x - 1, y, arr, gemType);
	findConnectedGems_(x, y + 1, arr, gemType);
	findConnectedGems_(x, y - 1, arr, gemType);
}
std::vector<int> GameScene::findConnectedGems(int x, int y) {

	std::vector<int> connected;
//	if (gBoard.at(x + y*kBoardWidth) <= -1) return;
//	findConnectedGems_(x, y, connected, gBoard.at(x + y*kBoardWidth));

	return connected;
}

void GameScene::createWorld() {
	//���� ��������
	//�߷��� ����

	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	//�������
	_world = new b2World(gravity);

	//�޽Ļ����ϋ� ���Ե� �ٵ����  ���߰� �Ұ����� �����Ѵ�
	_world->SetAllowSleeping(true);

	//�������� �����ۿ��� �Ұ����� �����Ѵ�
	_world->SetContinuousPhysics(true);

	//�����ڸ�(�׵θ�)�� ������ ������ �����

	//�ٵ����� ��ǥ�� �����Ѵ�
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	//���忡 �ٵ����� ����(��ǥ)�� �ٵ� �����
	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

	//�����ڸ�(�׷縮) ��輱�� �׸��� �ִ� ����� ��ü�� �����
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//���� ����� ��ü��  set(��1 , ��2)�� ���� �����
	//�׸��� �ٵ�(groundBody)�� ���(groundEdge)�� ������Ų��

	//�Ʒ���
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//����
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//����
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//�����U
	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);


	//������� ��-----------------------------------------------------------------
	this->schedule(schedule_selector(GameScene::tick));
}

void GameScene::tick(float dt) {
	//������ ��ġ�� �̿��� �׷��� ��ġ�� �����Ѵ�
	//velocityIterations : �ٵ���� ���������� �̵���Ű�� ���� �ʿ��� �浹���� �ݺ������� ���
	//positionIterations : ����Ʈ �и��� ��ħ ������ ���̱� ���� �ٵ��� ��ġ�� �ݺ������� ����
	//���� Ŭ���� ��Ȯ�� ������ ���������� ������ ��������

	//������Ʈ ������ �⺻��
	//int velocityIterations = 8;
	//int positionIterations = 3;

	//�޴��� ���� ���尪
	int velocityIterations = 8;
	int positionIterations = 3;

	//Step : �������踦 �ùķ��̼� �Ѵ�.
	_world->Step(dt, velocityIterations, positionIterations);

	//��� ���� ��ü���� ��ũ�� ����Ʈ�� ����Ǿ� ������ ���� �ְ� �������ִ�
	//������� ��ü��ŭ ������ �����鼭 �ٵ� ���� ��������Ʈ�� ���⼭ �����Ѵ�.
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {

			auto spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x*PTM_RATIO,
				b->GetPosition().y*PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));

		}
	}
}

void GameScene::addNewSpriteAtPosition(Vec2 location) {

	//�������̵带 �Ķ���ͷ� �Ѿ�� ��ġ�� �����s
	Sprite* pSprite = Sprite::createWithTexture(texture, Rect(0, 0, 40, 40));
	pSprite->setPosition(Vec2(location.x, location.y));
	this->addChild(pSprite);
	
	//�ٵ����� ����� �Ӽ��� �����Ѵ�
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	//���������Ϳ� ��������Ʈ�� ���δ�
	bodyDef.userData = pSprite;
	b2Body* body = _world->CreateBody(&bodyDef);


	// �ڽ� ����� ��ü ����

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.1f;
	body->CreateFixture(&fixtureDef);
	
}
void GameScene::checkTime(float t) {

	gameTime -= 2;
	float a = (gameTime % 100) * 0.8f / 100;
	//log("%f", a);
	timeBar->setScaleX(a);
	timeBar->setScaleY(0.8f);
	
	if (a < 0) {
		log("Game Over");
	}
}