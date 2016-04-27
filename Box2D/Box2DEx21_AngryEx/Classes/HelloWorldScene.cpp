#include "HelloWorldScene.h"

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
	log("init");

	auto sprite = Sprite::create("bg.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, -1);

	sprite = Sprite::create("catapult_base_2.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(181.0, FLOOR_HEIGHT));
	this->addChild(sprite, 0);

	sprite = Sprite::create("squirrel_1.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(11.0, FLOOR_HEIGHT));
	this->addChild(sprite, 0);

	sprite = Sprite::create("catapult_base_1.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(181.0, FLOOR_HEIGHT));
	this->addChild(sprite, 9);

	sprite = Sprite::create("squirrel_2.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(240.0, FLOOR_HEIGHT));
	this->addChild(sprite, 9);

	sprite = Sprite::create("fg.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, 10);

	if (createBox2dWorld(true)) {
		this->schedule(schedule_selector(HelloWorld::tick));
	}

	return true;
}

bool HelloWorld::createBox2dWorld(bool debug) {

	log("createBox2dWorld");
	Size screenSize = Director::getInstance()->getWinSize();

	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner

									  // Call the body factory which allocates memory for the ground body
									  // from a pool and creates the ground box shape (also from a pool).
									  // The body is also added to the world.
	m_groundBody = m_world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	// bottom
	groundEdge.Set(b2Vec2(0, FLOOR_HEIGHT / PTM_RATIO), b2Vec2(screenSize.width*2.0f / PTM_RATIO, FLOOR_HEIGHT / PTM_RATIO));
	m_groundBody->CreateFixture(&boxShapeDef);

	// top
	groundEdge.Set(b2Vec2(0, screenSize.height / PTM_RATIO), b2Vec2(screenSize.width*2.0f / PTM_RATIO, screenSize.height / PTM_RATIO));
	m_groundBody->CreateFixture(&boxShapeDef);

	// left
	groundEdge.Set(b2Vec2(0, screenSize.height / PTM_RATIO), b2Vec2(0, 0));
	m_groundBody->CreateFixture(&boxShapeDef);

	// right
	groundEdge.Set(b2Vec2(screenSize.width*2.0f / PTM_RATIO, screenSize.height / PTM_RATIO), b2Vec2(screenSize.width*2.0f / PTM_RATIO, 0));
	m_groundBody->CreateFixture(&boxShapeDef);

	// Create the catapult's arm
	//
	auto arm = Sprite::create("catapult_arm.png");
	this->addChild(arm, 1);

	b2BodyDef armBodyDef;
	armBodyDef.type = b2_dynamicBody;
	armBodyDef.linearDamping = 1;
	armBodyDef.angularDamping = 1;
	armBodyDef.position.Set(230.0f / PTM_RATIO, (FLOOR_HEIGHT + 91.0f) / PTM_RATIO);
	armBodyDef.userData = arm;
	m_armBody = m_world->CreateBody(&armBodyDef);

	b2PolygonShape armBox;
	armBox.SetAsBox(11.0f / PTM_RATIO, 91.0f / PTM_RATIO);
	b2FixtureDef armBoxDef;
	armBoxDef.shape = &armBox;
	armBoxDef.density = 0.3F;
	m_armFixture = m_armBody->CreateFixture(&armBoxDef);

	b2RevoluteJointDef armJointDef;
	armJointDef.Initialize(m_groundBody, m_armBody, b2Vec2(233.0f / PTM_RATIO, FLOOR_HEIGHT / PTM_RATIO));
	armJointDef.enableMotor = true;
	armJointDef.enableLimit = true;
	armJointDef.motorSpeed = -10; //-1260;
	armJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(9);
	armJointDef.upperAngle = CC_DEGREES_TO_RADIANS(75);
	armJointDef.maxMotorTorque = 700;
	m_armJoint = (b2RevoluteJoint*)m_world->CreateJoint(&armJointDef);

	m_mouseJoint = NULL;

	// set up the time delay
	auto delayAction = DelayTime::create(0.5f);
	// perform the selector call
	auto callSelectorAction = CallFunc::create(this, callfunc_selector(HelloWorld::resetGame));
	this->runAction(Sequence::create(delayAction,
		callSelectorAction,
		NULL));

	return true;
}

HelloWorld::~HelloWorld() {
	log("~HelloWorld");
	delete m_world;
	m_world = nullptr;
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);
	log("draw");
	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	log("onDraw");
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	m_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	log("onEnter");
	auto listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(
		EventListener::Type::TOUCH_ALL_AT_ONCE);
	log("onExit");
	Layer::onExit();
}

void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,
	cocos2d::Event* event) {

	if (m_mouseJoint != NULL)
	{
		return;
	}

	auto *myTouch = touches[0];
	auto location = myTouch->getLocation();
	location = this->convertToWorldSpace(location);
	b2Vec2 locationWorld = b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO);

	if (locationWorld.x < m_armBody->GetWorldCenter().x + 50.0 / PTM_RATIO)
	{
		b2MouseJointDef md;
		md.bodyA = m_groundBody;
		md.bodyB = m_armBody;
		md.target = locationWorld;
		md.maxForce = 2000;

		m_mouseJoint = (b2MouseJoint *)m_world->CreateJoint(&md);
	}

}

void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches,
	cocos2d::Event* event) {

	if (m_mouseJoint == NULL)
	{
		return;
	}

	auto *myTouch = touches[0];
	auto location = myTouch->getLocation();
	location = this->convertToWorldSpace(location);
	b2Vec2 locationWorld = b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO);

	m_mouseJoint->SetTarget(locationWorld);

}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches,
	cocos2d::Event* event) {

	if (m_mouseJoint != NULL)
	{
		if (m_armJoint->GetJointAngle() >= CC_DEGREES_TO_RADIANS(20))
		{
			m_releasingArm = true;
		}

		m_world->DestroyJoint(m_mouseJoint);
		m_mouseJoint = NULL;
		return;
	}

}


void HelloWorld::tick(float dt) {
	log("tick");
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	m_world->Step(dt, velocityIterations, positionIterations);

	//Iterate over the bodies in the physics world
	for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			//Synchronize the AtlasSprites position and rotation with the corresponding body
			auto myActor = (Sprite*)b->GetUserData();
			myActor->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

	// Arm is being released
	if (m_releasingArm && m_bulletJoint != NULL)
	{
		// Check if the arm reached the end so we can return the limits
		if (m_armJoint->GetJointAngle() <= CC_DEGREES_TO_RADIANS(10))
		{
			m_releasingArm = false;

			// Destroy joint so the bullet will be free
			m_world->DestroyJoint(m_bulletJoint);
			m_bulletJoint = nullptr;

			// set up the time delay
			auto delayAction = DelayTime::create(5);
			// perform the selector call
			auto callSelectorAction = CallFunc::create(this,
				callfunc_selector(HelloWorld::resetBullet));
			// run the action
			this->runAction(Sequence::create(delayAction,
				callSelectorAction,
				nullptr));
		}
	}

	// Bullet is moving.
	if (m_bulletBody && m_bulletJoint == NULL)
	{
		b2Vec2 position = m_bulletBody->GetPosition();
		CCPoint myPosition = this->getPosition();
		CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

		// Move the camera.
		if (position.x > screenSize.width / 2.0f / PTM_RATIO)
		{
			myPosition.x = -MIN(screenSize.width * 2.0f - screenSize.width, position.x * PTM_RATIO - screenSize.width / 2.0f);
			this->setPosition(myPosition);
		}
	}

}

void HelloWorld::createBullets(int count)
{
	log("createBullets");
	m_currentBullet = 0;
	float pos = 62.0f;

	if (count > 0)
	{
		// delta is the spacing between corns
		// 62 is the position o the screen where we want the corns to start appearing
		// 165 is the position on the screen where we want the corns to stop appearing
		// 30 is the size of the corn

		float delta = (count > 1) ? ((165.0f - 62.0f - 30.0f) / (count - 1)) : 0.0f;


		for (int i = 0; i<count; i++, pos += delta)
		{
			// Create the bullet
			//
			auto sprite = Sprite::create("acorn.png");
			this->addChild(sprite, 1);

			b2BodyDef bulletBodyDef;
			bulletBodyDef.type = b2_dynamicBody;
			bulletBodyDef.bullet = true;
			bulletBodyDef.position.Set(pos / PTM_RATIO, (FLOOR_HEIGHT + 15.0f) / PTM_RATIO);
			bulletBodyDef.userData = sprite;
			b2Body *bullet = m_world->CreateBody(&bulletBodyDef);
			bullet->SetActive(false);

			b2CircleShape circle;
			circle.m_radius = 15.0 / PTM_RATIO;

			b2FixtureDef ballShapeDef;
			ballShapeDef.shape = &circle;
			ballShapeDef.density = 0.8f;
			ballShapeDef.restitution = 0.2f;
			ballShapeDef.friction = 0.99f;
			bullet->CreateFixture(&ballShapeDef);

			m_bullets.push_back(bullet);
		}
	}
}

void HelloWorld::createTargets()
{
	log("createTargets");
	m_targets.clear();
	m_enemies.clear();

	// First block
	this->createTarget("brick_2.png", Vec2(675.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(741.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(741.0, FLOOR_HEIGHT + 23.0f), 0.0f, false, false, false);
	this->createTarget("brick_3.png", Vec2(672.0, FLOOR_HEIGHT + 46.0f), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(707.0, FLOOR_HEIGHT + 58.0f), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(707.0, FLOOR_HEIGHT + 81.0f), 0.0f, false, false, false);

	this->createTarget("head_dog.png", Vec2(702.0, FLOOR_HEIGHT), 0.0f, true, false, true);
	this->createTarget("head_cat.png", Vec2(680.0, FLOOR_HEIGHT + 58.0f), 0.0f, true, false, true);
	this->createTarget("head_dog.png", Vec2(740.0, FLOOR_HEIGHT + 58.0f), 0.0f, true, false, true);

	// 2 bricks at the right of the first block
	this->createTarget("brick_2.png", Vec2(770.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget("brick_2.png", Vec2(770.0, FLOOR_HEIGHT + 46.0f), 0.0f, false, false, false);

	// The dog between the blocks
	this->createTarget("head_dog.png", Vec2(830.0, FLOOR_HEIGHT), 0.0f, true, false, true);

	// Second block
	this->createTarget("brick_platform.png", Vec2(839.0, FLOOR_HEIGHT), 0.0f, false, true, false);
	this->createTarget("brick_2.png", Vec2(854.0, FLOOR_HEIGHT + 28.0f), 0.0f, false, false, false);
	this->createTarget("brick_2.png", Vec2(854.0, FLOOR_HEIGHT + 28.0f + 46.0f), 0.0f, false, false, false);
	this->createTarget("head_cat.png", Vec2(881.0, FLOOR_HEIGHT + 28.0f), 0.0f, true, false, true);
	this->createTarget("brick_2.png", Vec2(909.0, FLOOR_HEIGHT + 28.0f), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(909.0, FLOOR_HEIGHT + 28.0f + 46.0f), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(909.0, FLOOR_HEIGHT + 28.0f + 46.0f + 23.0f), 0.0f, false, false, false);
	this->createTarget("brick_2.png", Vec2(882.0, FLOOR_HEIGHT + 108.0f), 90.0f, false, false, false);

}

void HelloWorld::createTarget(const char *imageName, Vec2 position, float rotation, bool isCircle, bool isStatic, bool isEnemy)
{
	log("createTarget");
	auto sprite = Sprite::create(imageName);
	this->addChild(sprite, 1);

	b2BodyDef bodyDef;
	bodyDef.type = isStatic ? b2_staticBody : b2_dynamicBody;
	bodyDef.position.Set((position.x + sprite->getContentSize().width / 2.0f) / PTM_RATIO,
		(position.y + sprite->getContentSize().height / 2.0f) / PTM_RATIO);
	bodyDef.angle = CC_DEGREES_TO_RADIANS(rotation);
	bodyDef.userData = sprite;
	b2Body *body = m_world->CreateBody(&bodyDef);
	b2CircleShape circle;
	b2PolygonShape box;

	b2FixtureDef boxDef;
	if (isCircle)
	{
		log("createTarget1");
		circle.m_radius = sprite->getContentSize().width / 2.0f / PTM_RATIO;
		boxDef.shape = &circle;
	}
	else
	{
		log("createTarget2");
		box.SetAsBox(sprite->getContentSize().width / 2.0f / PTM_RATIO, sprite->getContentSize().height / 2.0f / PTM_RATIO);
		boxDef.shape = &box;
	}

	if (isEnemy)
	{
		boxDef.userData = (void*)1;
		m_enemies.push_back(body);
	}
	boxDef.density = 0.5f;
	body->CreateFixture(&boxDef);
	log("createTarget3");
	m_targets.push_back(body);
}

bool HelloWorld::attachBullet()
{
	log("attachBullet");
	if (m_currentBullet < m_bullets.size())
	{
		m_bulletBody = (b2Body*)m_bullets.at(m_currentBullet++);
		m_bulletBody->SetTransform(b2Vec2(230.0f / PTM_RATIO, (155.0f + FLOOR_HEIGHT) / PTM_RATIO), 0.0f);
		m_bulletBody->SetActive(true);

		b2WeldJointDef weldJointDef;
		weldJointDef.Initialize(m_bulletBody, m_armBody, b2Vec2(230.0f / PTM_RATIO, (155.0f + FLOOR_HEIGHT) / PTM_RATIO));
		weldJointDef.collideConnected = false;

		m_bulletJoint = (b2WeldJoint*)m_world->CreateJoint(&weldJointDef);
		return true;
	}

	return false;
}

void HelloWorld::resetBullet()
{
	log("resetBullet");
	if (m_enemies.size() == 0)
	{
		// game over
		// We'll do something here later
	}
	else if (this->attachBullet())
	{
		this->runAction(MoveTo::create(2.0f, Vec2::ZERO));
	}
	else
	{
		// We can reset the whole scene here
		// Also, let's do this later
	}
}

void HelloWorld::resetGame()
{
	log("resetGame");
	this->createBullets(4);
	this->attachBullet();
	this->createTargets();
}