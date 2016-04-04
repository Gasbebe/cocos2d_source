#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
/*extensions 프로젝트 우클릭 구성 c++  일반  추가 포함 디렉터리에  
$(EngineRoot)를  추가
*/

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
class HelloWorld : public cocos2d::LayerColor, public cocos2d::extension::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);
	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::EditBox* editBox);

	cocos2d::extension::EditBox* m_pEditName;
	cocos2d::extension::EditBox* m_pEditPassword;
	cocos2d::extension::EditBox* m_pEditEmail;
};

#endif // __HELLOWORLD_SCENE_H__
