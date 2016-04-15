#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	
	return scene;
}

bool HelloWorld::init()
{

	if (!Layer::init())
	{
		return false;
	}
	crocMouthOpened = false;
	bPine = true;
	ropes = new std::vector<VRope*>;
	pinesBody = new std::vector<b2Body*>;
	//cndies =new std::vector<b2Body*>;

	winSize = Director::getInstance()->getWinSize();

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("Images/CutTheVerlet.plist");

	auto bg = Sprite::createWithSpriteFrameName("bg.png");
	bg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	croc_ = Sprite::createWithSpriteFrameName("croc_front_mouthclosed.png");
	croc_->setPosition(Vec2(winSize.width - 50, 50));
	this->addChild(croc_);

	if (createBox2dWorld(true)) {
		this->schedule(schedule_selector(HelloWorld::tick));
	}
	return true;
}

bool HelloWorld::createBox2dWorld(bool debug) {
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	if (debug) {
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;

		m_debugDraw->SetFlags(flags);
	}

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	groundBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, 0),
		b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//밧줄 이미지 로드
	ropeSpriteSheet = SpriteBatchNode::create("Images/rope_texture.png");
	this->addChild(ropeSpriteSheet);

	//아이템 추가
	b2Body* body1 = this->addNewSpriteAt(Vec2(winSize.width / 2, winSize.height * 2 / 3));

	this->createRope(groundBody, b2Vec2((winSize.width - 300) / PTM_RATIO, (winSize.height - 50)/PTM_RATIO),
		body1,
		body1->GetLocalCenter(),
		1.1f);
	this->createRope(groundBody, b2Vec2((winSize.width - 50) / PTM_RATIO, (winSize.height - 100)/PTM_RATIO),
		body1,
		body1->GetLocalCenter(),
		1.1f);

	return true;
}

HelloWorld::~HelloWorld() {
	delete _world;
	delete ropes;
	_world = nullptr;
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {

	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event) {
}

void HelloWorld::tick(float dt) {
	int velocityInterations = 8;
	int positionInterations = 3;

	_world->Step(dt, velocityInterations, positionInterations);

	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			Sprite* spriteData = (Sprite *)b->GetUserData();
			spriteData->setPosition(
				Vec2(b->GetPosition().x * PTM_RATIO,
					b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}


	std::vector<VRope*>::iterator rope;
	for (rope = ropes->begin(); rope != ropes->end(); ++rope) {
		(*rope)->update(dt);
		(*rope)->updateSprites();
	}

	if (bPine) {
		if (croc_->boundingBox().intersectsRect(pine->boundingBox())) {
			deletePine();
			changeCrocSprite();

			auto dd = DelayTime::create(0.2f);
			auto sp = Sequence::create(dd, CallFunc::create(CC_CALLBACK_0(HelloWorld::changeCrocSprite, this)), nullptr);
			croc_->runAction(sp);
		}
	}
}

b2Body* HelloWorld::addNewSpriteAt(Vec2 point) {

	pine = Sprite::createWithSpriteFrameName("pineapple.png");
	this->addChild(pine);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
	bodyDef.userData = pine;
	bodyDef.linearDamping = 0.3f;
	b2Body* body = _world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape sprteShape;

	b2Vec2 verts[] = {
		b2Vec2(-7.6f / PTM_RATIO, -34.4f / PTM_RATIO),
		b2Vec2(8.3f / PTM_RATIO, -34.4f / PTM_RATIO),
		b2Vec2(15.55f / PTM_RATIO, -27.15f / PTM_RATIO),
		b2Vec2(13.8f / PTM_RATIO, 23.05f / PTM_RATIO),
		b2Vec2(-3.35f / PTM_RATIO, 35.25f / PTM_RATIO),
		b2Vec2(-16.25f / PTM_RATIO, 25.55f / PTM_RATIO),
		b2Vec2(-15.55f / PTM_RATIO, -23.95f / PTM_RATIO),
	};

	sprteShape.Set(verts, 7);
	fixtureDef.shape = &sprteShape;
	fixtureDef.density = 30.0f;
	fixtureDef.filter.categoryBits = 0x01;
	fixtureDef.filter.maskBits = 0x01;

	body->CreateFixture(&fixtureDef);
	pinesBody->push_back(body);
	return body;
}


void HelloWorld::createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body*bodyB, b2Vec2 anchorbB, float32 sag) {

	b2RopeJointDef jd;
	jd.bodyA = bodyA;
	jd.bodyB = bodyB;
	jd.localAnchorA = anchorA;
	jd.localAnchorB = anchorbB;

	float32 ropeLength = (bodyA->GetWorldPoint(anchorA) - bodyB->GetWorldPoint(anchorbB)).Length()*sag;
	jd.maxLength = ropeLength;
	b2RopeJoint* ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);
	VRope* newRope = new VRope(ropeJoint, ropeSpriteSheet);

	//ropes.push_back(newRope);
	ropes->push_back(newRope);
}

//밧줄에 터치 조사
bool HelloWorld::checkLineIntersection(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4) {
	float denominator = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);

	if (denominator == 0.0f)
		return false;
	float ua = ((p4.x - p3.x)*(p1.y - p3.y) - (p4.y - p3.y) *(p1.x - p3.x)) / denominator;
	float ub = ((p2.x - p1.x)*(p1.y - p3.y) - (p2.y - p1.y) *(p1.x - p3.x)) / denominator;

	if (ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0) {
		return true;
	}

	return false;
}

b2Body* HelloWorld::createRopeTipBody() {

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 0.5f;
	b2Body *body = _world->CreateBody(&bodyDef);

	b2FixtureDef circleDef;
	b2CircleShape circle;
	circle.m_radius = 1.0f / PTM_RATIO;
	circleDef.shape = &circle;
	circleDef.density = 10.0f;

	circleDef.filter.maskBits = 0;
	body->CreateFixture(&circleDef);

	return body;
}


void HelloWorld::onTouchMoved(Touch *touch, Event *event) {

	Vec2 pt0 = touch->getPreviousLocation();
	Vec2 pt1 = touch->getLocation();

	std::vector<VRope *>::iterator rope;
	for (rope = ropes->begin(); rope != ropes->end(); ++rope) {

		std::vector<VStick *>::iterator stick;

		for (stick = (*rope)->getSticks().begin(); stick != (*rope)->getSticks().end(); ++stick) {
			Vec2 pa = (*stick)->getPointA()->point();
			Vec2 pb = (*stick)->getPointB()->point();

			if (this->checkLineIntersection(pt0, pt1, pa, pb)) {
				//cut rope
				b2Body *newBodyA = createRopeTipBody();
				b2Body *newBodyB = createRopeTipBody();

				VRope *newRope = (*rope)->cutRopeInStick((*stick), newBodyA, newBodyB);
				ropes->push_back(newRope);

				return;
			}
		}
	}
}
void HelloWorld::deletePine() {
	//removeChild(pine, false);
	//_world->De(body);
	bPine = false;

	std::vector<b2Body*>::iterator pi;
	for (pi = pinesBody->begin(); pi != pinesBody->end(); ++pi) {
		b2Body* b = (*pi);
		b->SetUserData(nullptr);
		removeChild(pine, false);
		//_world->DestroyBody(b);
	}
	
}
void HelloWorld::changeCrocSprite() {
	
	if (!crocMouthOpened) {
		croc_->setSpriteFrame("croc_front_mouthopen.png");
		crocMouthOpened = true;
	}
	else {
		croc_->setSpriteFrame("croc_front_mouthclosed.png");
	}

}