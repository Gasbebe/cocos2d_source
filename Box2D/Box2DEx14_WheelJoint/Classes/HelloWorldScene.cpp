﻿#include "HelloWorldScene.h"

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

	winSize = Director::getInstance()->getWinSize();
	texture = Director::getInstance()->
		getTextureCache()->
		addImage("blocks.png");


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

	b2Body *groundBody = _world->CreateBody(&groundBodyDef);

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

	//bDrag = false;
	//gbody = this->addNewSprite(Vec2(0, 0), Size(0, 0), b2_staticBody, nullptr, 0);
	b2WheelJointDef jd1;
	b2WheelJointDef jd2;



	body0 = this->addNewSprite(Vec2(340, 70), Size(100, 40), b2_dynamicBody, nullptr, 0);
	b2Body *body1 = this->addNewSprite(Vec2(310, 50), Size(30, 30), b2_dynamicBody, nullptr, 1);
	b2Body *body2 = this->addNewSprite(Vec2(370, 50), Size(30, 30), b2_dynamicBody, nullptr, 1);

	b2Vec2 axis(0.0f, 1.0f);

	jd1.Initialize(body0, body1, body1->GetPosition(), axis);
	jd1.enableMotor = true;
	jd1.motorSpeed = 30.0f;
	jd1.maxMotorTorque = 20;
	jd1.frequencyHz = 4.0f;

	jd2.Initialize(body0, body2, body2->GetPosition(), axis);
	jd2.enableMotor = true;
	jd2.motorSpeed = 30.0f;
	jd2.maxMotorTorque = 20;
	jd2.frequencyHz = 4.0f;

	//joint1을 생성하기 전에 위 모터의 속성들을 정의해야한다
	m_spring1 = (b2WheelJoint*)_world->CreateJoint(&jd1);
	m_spring2 = (b2WheelJoint*)_world->CreateJoint(&jd2);

	return true;
}

HelloWorld::~HelloWorld() {
	delete _world;
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

	//auto listener = EventListenerTouchOneByOne::create();

	//listener->setSwallowTouches(true);

	//listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	//listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HelloWorld::onExit() {
	//_eventDispatcher->removeAllEventListeners();

	Layer::onExit();
}
/*
bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
auto touchPoint = touch->getLocation();

if (b2Body *b = this->getBodyAtTab(touchPoint)) {
dragBody = b;
bDrag = true;

b2MouseJointDef md;
md.bodyA = gbody;
md.bodyB = dragBody;
md.target.Set(dragBody->GetPosition().x, dragBody->GetPosition().y);
md.maxForce = 300.0 * dragBody->GetMass();

mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
}
return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event) {
Vec2 touchPoint = touch->getLocation();

if (bDrag) {
mouseJoint->SetTarget(b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO));
}
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event) {
if (bDrag) {
_world->DestroyJoint(mouseJoint);
mouseJoint = nullptr;

dragBody->SetAwake(true);
}
bDrag = false;
}
*/
void HelloWorld::tick(float dt) {
	//log("%f", dt);
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
	log("%f", body0->GetPosition().x);
	log("%d          1111111", winSize.width / 2 / PTM_RATIO);

	if (body0->GetPosition().x < 2.0f) {
		log("za");
		m_spring1->SetMotorSpeed(-30);
		m_spring2->SetMotorSpeed(-30);

	}
	else if (body0->GetPosition().x > 12.0f) {
		m_spring1->SetMotorSpeed(30);
		m_spring2->SetMotorSpeed(30);
	}



}

b2Body* HelloWorld::addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type) {
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (spriteName) {
		if (strcmp(spriteName, "test") == 0) {
			int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
			Sprite* sprite = Sprite::createWithTexture(texture, Rect(32 * idx, 32 * idy, 32, 32));
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
		else {
			Sprite* sprite = Sprite::create(spriteName);
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
	}

	b2Body *body = _world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circle;

	if (type == 0) {
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);

		fixtureDef.shape = &dynamicBox;
	}
	else {
		circle.m_radius = (size.width / 2) / PTM_RATIO;

		fixtureDef.shape = &circle;
	}

	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);

	return body;
}
/*
b2Body* HelloWorld::getBodyAtTab(Vec2 p) {
b2Fixture *fix;
for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()) {
if (b->GetUserData() != nullptr) {
if (b->GetType() == b2_staticBody) continue;
fix = b->GetFixtureList();
if (fix->TestPoint(b2Vec2(p.x / PTM_RATIO, p.y / PTM_RATIO))) {
return b;
}
}
}
return NULL;
}
*/




void HelloWorld::Speed() {
}