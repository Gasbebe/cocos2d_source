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

    if ( !LayerColor::initWithColor(Color4B(0,0,0,255)) )
    {
        return false;
    }
    
    /////////////////////////////



    return true;
}
void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}
bool HelloWorld::onTouchBegan(Touch *touch, Event *event){
	auto touchPoint = touch->getLocation();
	this->showParticle(touchPoint);
	return true;
}

void HelloWorld::showParticle(Vec2 point) {
	const char* filename1 = "Particles/BoilingFoam.plist";
	const char* filename2 = "Particles/BurstPipe.plist";
	const char* filename3 = "Particles/Comet.plist";
	const char* filename4 = "Particles/ExplodingRing.plist";
	const char* filename5 = "Particles/Flower.plist";
	const char* filename6 = "Particles/Galaxy.plist";
	const char* filename7 = "Particles/LavaFlow.plist";
	const char* filename8 = "Particles/Phoenix.plist";
	const char* filename9 = "Particles/SmallSun.plist";
	const char* filename10 = "Particles/SpinningPeas.plist";
	const char* filename11 = "Particles/Sprial.plist";
	const char* filename12 = "Particles/SpookyPeas.plist";
	const char* filename13 = "Particles/TestPremultipliedAlpha.plist";
	const char* filename14 = "Particles/Upsidedown.plist";

	ParticleSystem* emitter = ParticleSystemQuad::create(filename1);
	emitter->setPosition(point);
	emitter->setDuration(2.0f);
	emitter->setAutoRemoveOnFinish(true);
	this->addChild(emitter);
}