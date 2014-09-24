//hello world scene

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui\UIWidget.h"
using namespace cocos2d::ui;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
	static HelloWorld* fundlayer;
    virtual bool init();  

    //start and close functions
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStartCallback(cocos2d::Ref* pSender);

	//level 1-9 up down
	void addlevel(cocos2d::Ref* pSender);
	void reducelevel(cocos2d::Ref* pSender);

	//centralkind 1-3 up down
	void addkind(cocos2d::Ref* pSender);
	void reducekind(cocos2d::Ref* pSender);

	//touchbutton include centralinformation
	void touchButton(cocos2d::Object* ,cocos2d::ui::TouchEventType);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
