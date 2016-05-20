#include "HelloWorldScene.h"


USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
#include "platform/android/jni/JniHelper.h"

#ifdef __cplusplus
extern "C"{
#endif
	jint Java_org_cocos2dx_cpp_AppActivity_cppSum(JNIEnv *env, jobject obj, jint a, jint b)
	{

	}
#ifdef __cplusplus
}
#endif
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

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	/////////////////////////////
	auto pMenItem1 = MenuItemFont::create("자바 메서드 호출 ",
		CC_CALLBACK_1(HelloWorld::callJavaMethod, this));
	pMenItem1->setColor(Color3B(0, 0, 0));

	auto menu = Menu::create(pMenItem1, nullptr);

	this->addChild(menu);


	return true;
}
void HelloWorld::callJavaMethod(Ref* pSender) {

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t
		, "org.cocos2dx.cpp.AppActivity"
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