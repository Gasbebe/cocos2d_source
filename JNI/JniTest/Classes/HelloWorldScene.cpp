#include "HelloWorldScene.h"


USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include "platform/android/jni/JniHelper.h"
#endif

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
	auto pMenItem1 = MenuItemFont::create("자바 메서드 호출 ",
										 CC_CALLBACK_1(HelloWorld::callJavaMethod, this));
	pMenItem1->setColor(Color3B(0,0,0));

	auto pMenItem2 = MenuItemFont::create("오픈 브라우져",
		CC_CALLBACK_1(HelloWorld::openWeb, this));
	pMenItem2->setPosition(Vec2(0, 100));
	pMenItem2->setColor(Color3B(0, 0, 0));

	auto menu = Menu::create(pMenItem1, pMenItem2, nullptr);

	this->addChild(menu);


    return true;
}
void HelloWorld::callJavaMethod(Ref* pSender) {

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	
	if (JniHelper::getStaticMethodInfo(t
		,"org.cocos2dx.cpp.AppActivity"
		, "JniTestFunc"
		, "()V"))
	{
		//함수호출
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		//release
		t.env->DeleteLocalRef(t.classID);
	}
#endif

}

void HelloWorld::openWeb(Ref* pSender) {

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t
		, "org.cocos2dx.cpp.AppActivity"
		, "OpenBrowser"
		, "()V"))
	{
		//함수호출
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		//release
		t.env->DeleteLocalRef(t.classID);
	}
#endif

}