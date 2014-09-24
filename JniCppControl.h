#ifndef JNI_CONTROL_H
#define JNI_CONTROL_H

#include "cocos2d.h"
#include "GameMain.h"
#include "resource.h"
#include "HelloWorldScene.h"
USING_NS_CC;
void jniupforce()
{
	if(GameMain::GAME_STATUS == 1)
	{
		if (GameMain::gravity <= 0.2)
				GameMain::gravity += 0.2;
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
	else
		return;
}
void jnidownforce()
{
	if(GameMain::GAME_STATUS == 1)
	{
		if (GameMain::gravity >= -0.2)
				GameMain::gravity -= 0.2;
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
	else
		return;
}
void poperror()
{
	if(GameMain::GAME_STATUS != 1)
	{
		PopupLayer* pl = PopupLayer::create("gobackground.png");
		pl->addButton("restartbutton.png","restartbutton_pu.png"," ",42);
		pl->addButton("quitbutton.png","quitbutton_pu.png"," ",40);
		HelloWorld::fundlayer->addChild(pl,100);
	}
	else
		return;
}
#endif