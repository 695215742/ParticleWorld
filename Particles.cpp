#include "GameMain.h"
#include "Particles.h"
#include "resource.h"
Particles::Particles(void)
{
	addCount = 0;
	GAME_STATUS = 0;
	particleList = Array::create();
	particleList->retain();
}

void Particles::onEnter()
{
	Node::onEnter();	
}

void Particles::update()
{
	addCount++;
	if (addCount > 120 &&  particleList->getReferenceCount() < 3 )
	{
		addOne();
		addCount = 0;
	}
	// Change particle's location & Delete particle attracted
	auto planet = (Sprite*)GameMain::fundlayer->getChildByTag(TAG_PLANET);
	auto boundX = planet->getContentSize().width / 2;
	auto boundY = planet->getContentSize().height / 2;
	auto winSize = Director::getInstance()->getVisibleSize();
	auto center = new Point(winSize.width / 2, winSize.height / 2);
	for (int i = 0; i < particleList->count(); i++)
	{
		auto s = (ParticleSystemQuad*)particleList->getObjectAtIndex(i);
		auto info = infoList[i];
		float PosX = s->getPositionX();
		float PosY = s->getPositionY();
		
		if (PosX > winSize.width || PosX < 0 || PosY > winSize.height || PosY < 0)
		{
			particleList->removeObjectAtIndex(i);
			std::vector<Particle*>::iterator iterator = infoList.begin() + i;
			infoList.erase(iterator);
			s->stopSystem();
			GameMain::fundlayer->removeChild(s);			
			continue;
		}

		//CCLog("Particle %d (%fd, %fd) 's new location: (%fd, %fd)", i, PosX, PosY, PosX + info->velocityX, PosY + info->velocityY);
		s->setPositionX(PosX + info->velocityX);
		s->setPositionY(PosY + info->velocityY);
	}
}

void Particles::addOne()
{
	auto winSize = Director::getInstance()->getVisibleSize();
	// Add info
	auto info = new Particle();
	infoList.push_back(info);
	info->identity = CCRANDOM_0_1()*(GameMain::page/2);
	if(info->identity>0.5)
		info->identity = 2;
	else
		info->identity = 1;
	//Add sprite
	ParticleSystem* sprite;
	if(info->identity == 1)
	{
		int x = CCRANDOM_0_1() >0.5 ? 0 : 1;
		if(x==1)
		{
			info->identity = 1;
			sprite = creategoodnormal();
		}
		else
		{
			info->identity = 2;
			sprite = creategoodnormal2();
		}
	}
	else
	{
		int x = CCRANDOM_0_1() >0.5 ? 0 : 1;
		if(x==1)
		{
			info->identity = 3;
			sprite = createbadnormal();
		}
		else
		{
			info->identity = 4;
			sprite = createbadnormal2();
		}
	}
	particleList->addObject(sprite);
	sprite->setAutoRemoveOnFinish(true);
	this->addChild(sprite);
	// Set position and velocity
	int direction = 0;
	float roll = CCRANDOM_0_1();
	if (roll < 0.25) {}
	else if (roll < 0.5) direction = 1;
	else if (roll < 0.75) direction = 2;
	else if (roll <= 1) direction = 3;
	switch (direction)
	{
	case 0:
		// Add from North
		sprite->setPositionY(winSize.height);
		sprite->setPositionX(winSize.width * CCRANDOM_0_1());
		info->velocityX = 2 * CCRANDOM_0_1() * (CCRANDOM_0_1() < 0.5 ? 1 : -1);
		info->velocityY = 2 * CCRANDOM_0_1() * -1;
		break;
	case 1:
		// Add from East
		sprite->setPositionY(winSize.height * CCRANDOM_0_1());
		sprite->setPositionX(winSize.width);
		info->velocityX = 2 * CCRANDOM_0_1() * -1;
		info->velocityY = 2 * CCRANDOM_0_1() * (CCRANDOM_0_1() < 0.5 ? 1 : -1);
		break;
	case 2:
		// Add from South
		sprite->setPositionY(0);
		sprite->setPositionX(winSize.width * CCRANDOM_0_1());
		info->velocityX = 2 * CCRANDOM_0_1() * (CCRANDOM_0_1() < 0.5 ? 1 : -1);
		info->velocityY = 2 * CCRANDOM_0_1();
		break;
	case 3:
		// Add from West
		sprite->setPositionY(winSize.height * CCRANDOM_0_1());
		sprite->setPositionX(0);
		info->velocityX = 2 * CCRANDOM_0_1();
		info->velocityY = 2 * CCRANDOM_0_1() * (CCRANDOM_0_1() < 0.5 ? 1 : -1);
		break;
	}
}

ParticleSystemQuad* Particles::createbadnormal()
{
	auto targettmp = ParticleSystemQuad::create("targetplist/badnormal.plist");
	return targettmp;
}
ParticleSystemQuad* Particles::createbadnormal2()
{
	auto targettmp = ParticleSystemQuad::create("targetplist/badnormal2.plist");
	return targettmp;
}
ParticleSystemQuad* Particles::creategoodnormal()
{
	auto targettmp = ParticleSystemQuad::create("targetplist/goodnormal.plist");
	return targettmp;
}
ParticleSystemQuad* Particles::creategoodnormal2()
{
	auto targettmp = ParticleSystemQuad::create("targetplist/goodnormal2.plist");
	return targettmp;
}
