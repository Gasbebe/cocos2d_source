#include "HelloWorldScene.h"

static HelloWorld *g_pHello = NULL;

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include "platform/android/jni/JniHelper.h"

void callJavaMethod(std::string func) {
	JniMethodInfo t;
	/**
	JniHelper를 통해 org/cocos2dx/cpp/ 에있는
	AppActivity class의 파라미터로 들어온 스트링 이름의 함수 정보를 가져온다.
	*/
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/cpp/AppActivity"
		, func.c_str()
		, "()V"))
	{
		//함수호출
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		//release
		t.env->DeleteLocalRef(t.classID);
		
	}
}

#endif

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////
	auto pMenItem1 = MenuItemFont::create("do Show",
		CC_CALLBACK_1(HelloWorld::doShow, this));
	pMenItem1->setColor(Color3B(0, 0, 0));

	auto pMenItem2 = MenuItemFont::create("do Hide",
		CC_CALLBACK_1(HelloWorld::doHide, this));
	pMenItem2->setColor(Color3B(0, 0, 0));

	auto pMenItem3 = MenuItemFont::create("do FullShow",
		CC_CALLBACK_1(HelloWorld::doFullShow, this));
	pMenItem3->setColor(Color3B(0, 0, 0));

	auto menu = Menu::create(pMenItem1, pMenItem2, pMenItem3, nullptr);
	menu->alignItemsVerticallyWithPadding(10.0f);
	this->addChild(menu);

	////////////////////

	g_pHello = this;

	///////////////////
	return true;
}


void HelloWorld::doShow(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	callJavaMethod("ShowAdPopup");
#endif
}

void HelloWorld::doHide(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	callJavaMethod("HideAdPopup");
#endif
}

void HelloWorld::doFullShow(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	callJavaMethod("ShowAdFull");
#endif
}