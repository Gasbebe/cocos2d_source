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

	this->doParticles();

    return true;
}

void HelloWorld::doParticles() {
	//ParticleSystem* particleTest = ParticleFire::create();
	//ParticleSystem* particleTest = ParticleSun::create();
	//ParticleSystem* particleTest = ParticleGalaxy::create();
	//ParticleSystem* particleTest = ParticleSmoke::create();
	//ParticleSystem* particleTest = ParticleMeteor::create();
	//ParticleSystem* particleTest = ParticleFlower::create();
	ParticleSystem* particleTest = ParticleFireworks::create();
	//ParticleSystem* particleTest = ParticleExplosion::create();
	//ParticleSystem* particleTest = ParticleSpiral::create();
	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/fire.png");

	particleTest->setTexture(texture);

	if (particleTest != nullptr) {

		particleTest->setScale(1.0);
		//파티클 지속시간지정
		//particleTest->setDuration(1.0);

		//파티클의 위치 조정
		particleTest->setPosition(Vec2(240, 160));
		this->addChild(particleTest);
	}
}
