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
	UserDefault::getInstance()->setStringForKey("str_key", "value1");
	UserDefault::getInstance()->setIntegerForKey("int_key", 10);
	UserDefault::getInstance()->setFloatForKey("float_key", 2.3f);
	UserDefault::getInstance()->setDoubleForKey("double_key", 2.4f);
	UserDefault::getInstance()->setBoolForKey("bool_key", true);

	log("Valu1 ============================================================");

	std::string ret = UserDefault::getInstance()->getStringForKey("str_key");
	log("string %s ", ret.c_str());

	int i = UserDefault::getInstance()->getIntegerForKey("int_key");
	log("intrger is %d", i);

	float f = UserDefault::getInstance()->getFloatForKey("float_key");
	log("float is %f", f);

	double d = UserDefault::getInstance()->getDoubleForKey("double_key");
	log("double is %f", d);

	bool b = UserDefault::getInstance()->getBoolForKey("bool_key");
	if (b) {
		log("bool true");
	}
	else {
		log("bool false");
	}

	log("Valu2 ============================================================");
	//change the value

	UserDefault::getInstance()->setStringForKey("str_key", "value2");
	UserDefault::getInstance()->setIntegerForKey("int_key", 11);
	UserDefault::getInstance()->setFloatForKey("float_key", 2.5f);
	UserDefault::getInstance()->setDoubleForKey("double_key", 2.6f);
	UserDefault::getInstance()->setBoolForKey("bool_key", false);

	UserDefault::getInstance()->flush();

	//pint value
	ret = UserDefault::getInstance()->getStringForKey("str_key");
	log("string %s ", ret.c_str());
	i = UserDefault::getInstance()->getIntegerForKey("int_key");
	log("intrger is %d", i);
	f = UserDefault::getInstance()->getFloatForKey("float_key");
	log("float is %f", f);
	d = UserDefault::getInstance()->getDoubleForKey("double_key");
	log("double is %f", d);
	b = UserDefault::getInstance()->getBoolForKey("bool_key");
	if (b) {
		log("bool true");
	}
	else {
		log("bool false");
	}
	
    return true;
}

