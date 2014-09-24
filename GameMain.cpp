#include "GameMain.h"
#include "tinyxml2/tinyxml2.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
//init static valuable
using namespace cocos2d::ui;
using namespace tinyxml2;
int GameMain::GAME_STATUS = 0;
float GameMain::gravity = 0;
int GameMain::page = 1;
int GameMain::state = 1;
GameMain* GameMain::fundlayer;
int GameMain::score = 0;
int GameMain::centralkind = 1;
//construct function ,init score and life
GameMain::GameMain()
{
	this->life = 3;
}

Scene* GameMain::createScene()
{
    auto scene = Scene::create();
	auto layer = GameMain::create();;
	fundlayer = layer;
    scene->addChild(layer);

	/*
	std::string filePath = FileUtils::getInstance()->getWritablePath()+"progress.xml";
	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	pDoc->LoadFile(filePath.c_str());
	XMLElement *rootEle = pDoc->RootElement();
 
	//获取第一个节点属性
	const XMLAttribute *attribute = rootEle->FirstAttribute();
	//打印节点属性名和值
	log("attribute_name = %s,attribute_value = %s", attribute->Name(), attribute->Value());
	*/


	 return scene;
}

bool GameMain::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	//get size
	Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//import and init UI resource
	auto mainlayer = cocostudio::GUIReader::shareReader()->widgetFromJsonFile("MainUI/MainUI.json");
	mainlayer->setTag(1);
	ui::LoadingBar* score_bar = (ui::LoadingBar* )(mainlayer->getChildByTag(5)->getChildByTag(1));
	score_bar->setPercent(0);
	ui::TextAtlas* score_lbl = (ui::TextAtlas*)(mainlayer->getChildByTag(5)->getChildByTag(2));
	score_lbl->setString("0");

	//add touchevent of buttons
	ui::Button* pause_btn = (ui::Button *)(mainlayer->getChildByTag(5)->getChildByTag(3));
	pause_btn->addTouchEventListener(this,toucheventselector(GameMain::touchButton));
	ui::Button* up_btn = (ui::Button *)(mainlayer->getChildByTag(5)->getChildByTag(20));
	up_btn->addTouchEventListener(this,toucheventselector(GameMain::touchButton));
	ui::Button* down_btn = (ui::Button *)(mainlayer->getChildByTag(5)->getChildByTag(21));
	down_btn->addTouchEventListener(this,toucheventselector(GameMain::touchButton));
	up_btn->removeFromParent();
	down_btn->removeFromParent();
	//add central
	addcentral();
	//add around
	particles = new Particles();
	this->addChild(particles,10);

	//excute update
	scheduleUpdate();

	//add UI
	addChild(mainlayer,12);
	return true;
}

//close function
void GameMain::menuCloseCallback(Ref* pSender)
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

//pause function
void GameMain::menuPauseCallback(Ref* pSender)
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

//buttons' function ,include pause quit resume,upforce downforce
void GameMain::touchButton(Object* obj,TouchEventType eventType)  
{  
    auto button = dynamic_cast<ui::Button*>(obj);  
    int tag = button->getTag();
	log("dfasfdfdaf");
    switch(eventType)  
    {  
	case TouchEventType::TOUCH_EVENT_BEGAN:  
        if(tag == 3)  
        {  
			pause();
			PopupLayer* pl = PopupLayer::create("popbackground.png");
			pl->addButton("resumebutton.png","resumebutton_pu.png"," ",41);
			pl->addButton("quitbutton.png","quitbutton_pu.png"," ",40);
			addChild(pl,100);
        }  
        else if(tag == 20)
		{
			upforce();
        }
		else if(tag == 21)
		{
			downforce();
        }
    }  
}

//add central function
void GameMain::addcentral()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//init resource
	auto central = ParticleSystemQuad::createWithTotalParticles(100);
	central->setTag(99);
	addChild(central, 10);
	central->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
	central->setAnchorPoint(Point(0, 0));
	// duration
	central->setDuration(ParticleSystem::DURATION_INFINITY);
 
	/*// radius mode
	central->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	central->setGravity(Vec2(visibleSize.width/2,visibleSize.height/2));
	// radius mode: start and end radius in pixels
	central->setStartRadius(30);
	central->setStartRadiusVar(10);
	central->setEndRadius(30);
	central->setEndRadiusVar(10);
 
	// radius mode: degrees per second
	central->setRotatePerSecond(30);
	central->setRotatePerSecondVar(0);*/

	//start radius&end radius
	central->setEmitterMode(ParticleSystem::Mode::RADIUS);
	central->setStartRadius(200);
	central->setStartRadiusVar(200);
	central->setEndRadius(200);
	central->setEndRadiusVar(200);
	// angle
	central->setAngle(360);
	central->setAngleVar(360);
	// emitter position
	auto size = Director::getInstance()->getWinSize();
	central->setPosVar(Vec2(300,300));
	// life of particles
	central->setLife(2);
	central->setLifeVar(0.5);
	//central->setSpeed(100);
	// spin of particles
	central->setStartSpin(0);
	central->setStartSpinVar(0);
	central->setEndSpin(0);
	central->setEndSpinVar(0);
 
	// color of particles
	Color4F startColor(0.0, 0.51, 0.63, 1.0f);
	central->setStartColor(startColor);
 
	Color4F startColorVar(0.5, 0.5, 0.5, 0);
	central->setStartColorVar(startColorVar);
 
	Color4F endColor(0.15,0.4,0.4,0);
	central->setEndColor(endColor);
 
	Color4F endColorVar(0.5, 0.5, 0.5, 0);
	central->setEndColorVar(endColorVar);
 
	// size, in pixels
	central->setStartSize(10);
	central->setStartSizeVar(8);
	central->setEndSize(5);
	central->setEndSizeVar(8);
	// emits per second
	central->setEmissionRate(central->getTotalParticles() / central->getLife());
 
	// additive
	central->setBlendAdditive(false);
 
	//addChild(central);
	central->setPosition(Point(visibleSize.width/2,visibleSize.height/2));

	//add central heart
	String* s = String::createWithFormat("targetplist/central%d.plist", GameMain::centralkind);
	auto centralheart = ParticleSystemQuad::create(s->getCString());
	centralheart->setTag(103);
	centralheart->setPosition(visibleSize.width/2,visibleSize.height/2);
	addChild(centralheart, 11);

	//word control
	Sprite* wordprase = Sprite::create("readygo.png");
	wordprase->setPosition(visibleSize.width/2,visibleSize.height/2);
	FadeOut* wordaction = FadeOut::create(1.6);
	wordprase->runAction(wordaction);
	addChild(wordprase,12,33);
}

void GameMain::update(float time)
{
	if(score >= 20)
	{
		pause();
		newtask();
	}
	else if(score<0)
	{
		pause();
		gameover();
	}
	else if(score == 5)
	{
		if(state != 2)
		{
			Sprite* word = (Sprite*)getChildByTag(33);
			CCSprite * temp_obj = CCSprite::create("good.png");   
			CCTexture2D *n_level;
			n_level = temp_obj->getTexture();
			word->setTexture(n_level);
			FadeIn* wordin = FadeIn::create(0.5); 
			FadeOut* wordout = FadeOut::create(0.5);
			Sequence* wordsequence = Sequence::create(wordin,wordout,NULL);
			word->runAction(wordsequence);
			state = 2;
		}
	}
	else if(score == 10)
	{
		if(state != 3)
		{
			Sprite* word = (Sprite*)getChildByTag(33);
			CCSprite * temp_obj = CCSprite::create("excellent.png");   
			CCTexture2D *n_level;
			n_level = temp_obj->getTexture();
			word->setTexture(n_level);
			FadeIn* wordin = FadeIn::create(0.5); 
			FadeOut* wordout = FadeOut::create(0.5);
			Sequence* wordsequence = Sequence::create(wordin,wordout,NULL);
			word->runAction(wordsequence);
			state = 3;
		}
	}
	else if(score == 15)
	{
		if(state != 4)
		{
			Sprite* word = (Sprite*)getChildByTag(33);
			CCSprite * temp_obj = CCSprite::create("amazing.png");   
			CCTexture2D *n_level;
			n_level = temp_obj->getTexture();
			word->setTexture(n_level);
			FadeIn* wordin = FadeIn::create(0.5); 
			FadeOut* wordout = FadeOut::create(0.5);
			Sequence* wordsequence = Sequence::create(wordin,wordout,NULL);
			word->runAction(wordsequence);
			state = 4;
		}
	}
	auto winSize = Director::getInstance()->getVisibleSize();
	auto planet = this->getChildByTag(TAG_PLANET);
	Rect rPlanet = ((Sprite*)planet)->getBoundingBox();
	rPlanet.setRect(winSize.width/2-40,winSize.height/2-40,80,80);
	
	for (int i = 0; i < particles->particleList->count(); i++)
	{
		Sprite* particleSprite = (Sprite*)particles->particleList->getObjectAtIndex(i);
		Particle* particleInfo = (Particle*)particles->infoList[i];
		Rect rtarget = particleSprite->getBoundingBox();
		// Judge Crash
		float PosX = particleSprite->getPositionX();
		float PosY = particleSprite->getPositionY();
		int loc = 0;			
		int edge1 = abs(winSize.width / 2 - PosX);
		int edge2 = abs(winSize.height / 2 - PosY);
		int edge3 = sqrtf(pow(edge1, 2) + pow(edge2, 2));
		particleSprite->runAction(DelayTime::create(4));
		if (edge3<=90)
		{

			if (particleInfo->identity == 1)
			{
				score++;
				ui::TextAtlas* score_lbl = (ui::TextAtlas*)(this->getChildByTag(1)->getChildByTag(5)->getChildByTag(2));
				String* s = String::createWithFormat("%d", score*5);
				score_lbl->setStringValue(s->getCString());
				auto sp = (ParticleSystemQuad*)particles->particleList->getObjectAtIndex(i);
				sp->stopSystem();
				ParticleSystemQuad * explode = ParticleSystemQuad::create("targetplist/goodnormal_ex.plist");
				Vec2 temp = particleSprite->getPosition();
				explode->setPosition( temp.x,temp.y);
				addChild(explode);
				explode->setAutoRemoveOnFinish(true);
				particles->particleList->removeObjectAtIndex(i);
				std::vector<Particle*>::iterator iterator = particles->infoList.begin() + i;
				iterator = particles->infoList.erase(iterator);
				this->removeChild(sp);
				ui::LoadingBar* score_bar = (ui::LoadingBar* )(this->getChildByTag(1)->getChildByTag(5)->getChildByTag(1));
				score_bar->setPercent(score*5);
				continue;
			}
			else if (particleInfo->identity == 2)
			{
				score++;
				ui::TextAtlas* score_lbl = (ui::TextAtlas*)(this->getChildByTag(1)->getChildByTag(5)->getChildByTag(2));
				String* s = String::createWithFormat("%d", score*5);
				score_lbl->setStringValue(s->getCString());
				auto sp = (ParticleSystemQuad*)particles->particleList->getObjectAtIndex(i);
				sp->stopSystem();
				ParticleSystemQuad * explode = ParticleSystemQuad::create("targetplist/goodnormal2_ex.plist");
				Vec2 temp = particleSprite->getPosition();
				explode->setPosition( temp.x,temp.y);
				addChild(explode);
				explode->setAutoRemoveOnFinish(true);
				particles->particleList->removeObjectAtIndex(i);
				std::vector<Particle*>::iterator iterator = particles->infoList.begin() + i;
				iterator = particles->infoList.erase(iterator);
				this->removeChild(sp);
				ui::LoadingBar* score_bar = (ui::LoadingBar* )(this->getChildByTag(1)->getChildByTag(5)->getChildByTag(1));
				score_bar->setPercent(score*5);
				continue;
			}
			else if (particleInfo->identity == 3)
			{
				score--;
				ui::TextAtlas* score_lbl = (ui::TextAtlas*)(this->getChildByTag(1)->getChildByTag(5)->getChildByTag(2));
				String* s = String::createWithFormat("%d", score*5);
				score_lbl->setStringValue(s->getCString());
				auto sp = (ParticleSystemQuad*)particles->particleList->getObjectAtIndex(i);
				sp->stopSystem();
				ParticleSystemQuad * explode = ParticleSystemQuad::create("targetplist/badnormal_ex.plist");
				Vec2 temp = particleSprite->getPosition();
				explode->setPosition( temp.x,temp.y);
				addChild(explode);
				explode->setAutoRemoveOnFinish(true);
				particles->particleList->removeObjectAtIndex(i);
				std::vector<Particle*>::iterator iterator = particles->infoList.begin() + i;
				iterator = particles->infoList.erase(iterator);
				this->removeChild(sp);
				ui::LoadingBar* score_bar = (ui::LoadingBar* )(this->getChildByTag(1)->getChildByTag(5)->getChildByTag(1));
				score_bar->setPercent(score*5);
				continue;
			}
			else if (particleInfo->identity == 4)
			{
				score--;
				ui::TextAtlas* score_lbl = (ui::TextAtlas*)(this->getChildByTag(1)->getChildByTag(5)->getChildByTag(2));
				String* s = String::createWithFormat("%d", score*5);
				score_lbl->setStringValue(s->getCString());
				auto sp = (ParticleSystemQuad*)particles->particleList->getObjectAtIndex(i);
				sp->stopSystem();
				ParticleSystemQuad * explode = ParticleSystemQuad::create("targetplist/badnormal2_ex.plist");
				Vec2 temp = particleSprite->getPosition();
				explode->setPosition( temp.x,temp.y);
				addChild(explode);
				explode->setAutoRemoveOnFinish(true);
				particles->particleList->removeObjectAtIndex(i);
				std::vector<Particle*>::iterator iterator = particles->infoList.begin() + i;
				iterator = particles->infoList.erase(iterator);
				this->removeChild(sp);
				ui::LoadingBar* score_bar = (ui::LoadingBar* )(this->getChildByTag(1)->getChildByTag(5)->getChildByTag(1));
				score_bar->setPercent(score*5);
				continue;
			}
			//scoreSprite->setString(s->getCString());
			//sp->setVisible(false);
		}
		// Change velocity
		{
			if (particleSprite->getPositionX() < winSize.width / 2)
			{
				particleInfo->velocityX += gravity / edge3 * edge1;
				if (particleSprite->getPositionY() < winSize.height / 2) // Third quadrant
					particleInfo->velocityY += gravity / edge3 * edge2 ;
				else // Second quadrant
					particleInfo->velocityY -= gravity / edge3 * edge2;
			}
			else
			{
				particleInfo->velocityX -= gravity / edge3 * edge1;
				if (particleSprite->getPositionY() < winSize.height / 2) // Fourth quadrant
					particleInfo->velocityY += gravity / edge3 * edge2 ;
				else // First quadrant
					particleInfo->velocityY -= gravity / edge3 * edge2 ;
			}
		}
	}
	particles->update();
}
void GameMain::upforce()
{
	if (GameMain::gravity <= 0.1)
			GameMain::gravity += 0.1;
	if(GameMain::gravity>0)
	{		
		ParticleSystemQuad* around = (ParticleSystemQuad *)GameMain::fundlayer->getChildByTag(99);
		int refirstsize = around->getStartRadius();
		int reendsize = around->getEndRadius();
		around->setStartRadiusVar(50);
		around->setEndRadiusVar(50);
		around->setEndRadius(20);
		around->setStartRadius(250);
	}
	else if(GameMain::gravity == 0)
	{
		ParticleSystemQuad* around = (ParticleSystemQuad *)GameMain::fundlayer->getChildByTag(99);
		around->setStartRadius(200);
		around->setEndRadius(200);
		around->setStartRadiusVar(200);
		around->setEndRadiusVar(200);
	}
}
void GameMain::downforce()
{
	if (GameMain::gravity >= -0.1)
			GameMain::gravity -= 0.1;
	if(GameMain::gravity == 0)
	{
		ParticleSystemQuad* around = (ParticleSystemQuad *)GameMain::fundlayer->getChildByTag(99);
		around->setStartRadius(200);
		around->setEndRadius(200);
		around->setStartRadiusVar(200);
		around->setEndRadiusVar(200);
	}
	else if(GameMain::gravity<0)
	{
		ParticleSystemQuad* around = (ParticleSystemQuad *)GameMain::fundlayer->getChildByTag(99);
		int refirstsize = around->getStartRadius();
		int reendsize = around->getEndRadius();
		around->setStartRadius(20);
		around->setStartRadiusVar(50);
		around->setEndRadiusVar(50);
		around->setEndRadius(250);
	}
}
void GameMain::newtask()
{
	PopupLayer* pl = PopupLayer::create("nextbackground.png");
	pl->addButton("nextbutton.png","nextbutton_pu.png"," ",43);
	pl->addButton("quitbutton.png","quitbutton_pu.png"," ",40);
	addChild(pl,100);
}

void GameMain::gameover()
{
	PopupLayer* pl = PopupLayer::create("gobackground.png");
	pl->addButton("restartbutton.png","restartbutton_pu.png"," ",42);
	pl->addButton("quitbutton.png","quitbutton_pu.png"," ",40);
	addChild(pl,100);
}