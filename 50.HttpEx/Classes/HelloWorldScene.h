#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"

using namespace cocos2d;
using namespace network;

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);

	void onGetTest(cocos2d::Ref* sender);
	void onPostTest(cocos2d::Ref* sender);
	void onPostBinaryTest(cocos2d::Ref* sender);

	void onHttpRequestCompleted(HttpClient* sender, HttpResponse* reponse);
	cocos2d::LabelTTF* _labelStatusCode;
};

#endif // __HELLOWORLD_SCENE_H__
