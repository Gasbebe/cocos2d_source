#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d::extension;

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
	Size editBoxSize = Size(300, 60);
	m_pEditName = EditBox::create(editBoxSize, Scale9Sprite::create("extensions/orange_edit.png"));
	m_pEditName->setPosition(Vec2(240, 250));
	m_pEditName->setFontColor(Color3B::GREEN);
	m_pEditName->setPlaceHolder("Name:");
	m_pEditName->setMaxLength(8);
	m_pEditName->setReturnType(EditBox::KeyboardReturnType::DONE);
	m_pEditName->setDelegate(this);
	addChild(m_pEditName);

	m_pEditPassword = EditBox::create(editBoxSize, Scale9Sprite::create("extensions/green_edit.png"));
	m_pEditPassword->setPosition(Vec2(240, 150));
	m_pEditPassword->setFontColor(Color3B::RED);
	m_pEditPassword->setPlaceHolder("password:");
	m_pEditPassword->setMaxLength(6);
	m_pEditPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
	m_pEditPassword->setInputMode(EditBox::InputMode::SINGLE_LINE);
	m_pEditPassword->setDelegate(this);
	addChild(m_pEditPassword);
	
	m_pEditEmail = EditBox::create(editBoxSize, Scale9Sprite::create("extensions/yellow_edit.png"));
	m_pEditEmail->setPosition(Vec2(240, 50));
	m_pEditEmail->setPlaceHolder("Email:");
	m_pEditEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
	m_pEditEmail->setDelegate(this);
	addChild(m_pEditEmail);

    return true;
}

void HelloWorld::editBoxEditingDidBegin(EditBox* editBox) {
	log("editBox %p editBoxEditingDidBegin!", editBox);
}
void HelloWorld::editBoxEditingDidEnd(EditBox* editBox) {
	log("editBox %p editBoxEditingDidEnd!", editBox);
}
void HelloWorld::editBoxTextChanged(EditBox* editBox, const std::string& text) {
	log("editBox %p editBoxTextChanged! Text : %s", editBox, text.c_str());
}
void HelloWorld::editBoxReturn(EditBox* editBox) {
	log("editBox %p  was returned");
}