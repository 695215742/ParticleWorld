#include "HelloWorldScene.h"
#include "cocostudio\CCArmatureDataManager.h"
#include "cocostudio\CCArmature.h"
#include "extensions\cocos-ext.h"
#include "GameMain.h"
#include "PopupLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
HelloWorld* HelloWorld::fundlayer;
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
	fundlayer = layer;
	GameMain::page = 1;
    return scene;
}

//init welcomescene
bool HelloWorld::init()
{
	//super init first
    if ( !Layer::init() )
    {
        return false;
    }
    //get size
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //add button and background
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	//background
    auto sprite = Sprite::create("welbackground.png");

    // set background position
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(sprite, 0);
	//add start button
	auto startItem = MenuItemImage::create(
                                           "startbutton.png",
                                           "startbutton_pu.png",
                                           CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
    
	startItem->setPosition(Vec2(visibleSize.width/2  ,
		visibleSize.height/7));

	//select page

	auto leftItem = MenuItemImage::create(
                                           "leftbtn.png",
                                           "leftbtn_pu.png",
                                           CC_CALLBACK_1(HelloWorld::reducelevel, this));
	leftItem->setPosition(Vec2(visibleSize.width/2 -leftItem->getContentSize().width ,
		visibleSize.height/2+leftItem->getContentSize().height/3));
	auto rightItem = MenuItemImage::create(
                                           "rightbtn.png",
                                           "rightbtn_pu.png",
                                           CC_CALLBACK_1(HelloWorld::addlevel, this));
	rightItem->setPosition(Vec2(visibleSize.width/2 +leftItem->getContentSize().width ,
		visibleSize.height/2+leftItem->getContentSize().height/3));

	Button* central = Button::create("ex1.png");
	central->setPosition(Vec2(visibleSize.width/2  ,
		visibleSize.height/2+leftItem->getContentSize().height/3));
	this->addChild(central,10,30);
	central->addTouchEventListener(this,toucheventselector(HelloWorld::touchButton));
	Sprite* level = Sprite::create("level1.png");
	level->setPosition(Vec2(visibleSize.width/2  ,
		visibleSize.height/2-leftItem->getContentSize().height/3));
	this->addChild(level,1,22);
	//select central
	auto leftItem_c = MenuItemImage::create(
                                           "leftbtn.png",
                                           "leftbtn_pu.png",
                                           CC_CALLBACK_1(HelloWorld::reducelevel, this));
	leftItem_c->setPosition(Vec2(visibleSize.width/2 -leftItem->getContentSize().width ,
		visibleSize.height/2-leftItem->getContentSize().height/3));
	auto rightItem_c = MenuItemImage::create(
                                           "rightbtn.png",
                                           "rightbtn_pu.png",
                                           CC_CALLBACK_1(HelloWorld::addlevel, this));
	rightItem_c->setPosition(Vec2(visibleSize.width/2 +leftItem->getContentSize().width ,
		visibleSize.height/2-leftItem->getContentSize().height/3));


	// create menu,include buttons and background
	auto menu = Menu::create(closeItem,startItem,leftItem, rightItem,rightItem_c,leftItem_c,NULL);
    menu->setPosition(Vec2::ZERO);
	//add menu
    this->addChild(menu, 1);
	


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
//start function
void HelloWorld::menuStartCallback(Ref* pSender)
{
	CCScene * scene1=GameMain::createScene();
	CCTransitionScene * ss=CCTransitionCrossFade::create(1,scene1);
	CCDirector::sharedDirector()->replaceScene(ss);
	GameMain::GAME_STATUS = 1;
}

void HelloWorld::addlevel(Ref* pSender)
{
	Sprite* level = (Sprite*)getChildByTag(22);
	CCTexture2D *n_level;
	if(GameMain::page <9)
	{
		++GameMain::page;
		String* s = String::createWithFormat("level%d.png",GameMain::page );
		CCSprite * temp_obj = CCSprite::create(s->getCString());   
		n_level = temp_obj->getTexture();
		level->setTexture(n_level);
	}
}
void HelloWorld::reducelevel(Ref* pSender)
{
	Sprite* level = (Sprite*)getChildByTag(22);
	CCTexture2D *n_level;
	if(GameMain::page>1)
	{
		GameMain::page--;
		String* s = String::createWithFormat("level%d.png", GameMain::page);
		CCSprite * temp_obj = CCSprite::create(s->getCString());   
		n_level = temp_obj->getTexture();
		level->setTexture(n_level);
	}
}
void HelloWorld::reducekind(Ref* pSender)
{
	Button* level = (Button*)getChildByTag(30);
	CCTexture2D *n_level;
	if(GameMain::page<3)
	{
		GameMain::centralkind--;
		String* s = String::createWithFormat("ex%d.png", GameMain::centralkind);
		level->removeFromParent();
		Button* newcentral = Button::create(s->getCString());
		addChild(newcentral,10,30);
		//Button* newcentral
	}
}
void HelloWorld::addkind(Ref* pSender)
{
	Button* level = (Button*)getChildByTag(30);
	CCTexture2D *n_level;
	if(GameMain::page>1)
	{
		GameMain::page--;
		String* s = String::createWithFormat("ex%d.png", GameMain::centralkind);
	}
}
void HelloWorld::touchButton(Object* obj,TouchEventType eventType)  
{  
    auto button = dynamic_cast<ui::Button*>(obj);  
	Size visibleSize = Director::getInstance()->getVisibleSize();
    int tag = button->getTag();
    switch(eventType)  
    {  
	case TouchEventType::TOUCH_EVENT_BEGAN:  
        if(tag == 30)  
        {  
			Button* btn = Button::create("central3.png");
			btn->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
			btn->addTouchEventListener(this,toucheventselector(HelloWorld::touchButton));
			addChild(btn,100,33);
        }
		else if(tag == 33)
		{
			getChildByTag(33)->removeFromParent();
		}
	}
}