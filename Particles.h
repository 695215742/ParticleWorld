#ifndef PARTICLES_H
#define PARTICLES_H

#include "cocos2d.h"
#include "Particle.h"

USING_NS_CC;

class Particles : public Node
{
public:
	Array* particleList;
	std::vector<Particle*> infoList;

	Particles();
	virtual void onEnter();
	void update();
	void addOne();
	void checkDel();

	//four kinds of particles
	ParticleSystemQuad* createbadnormal();
	ParticleSystemQuad* createbadnormal2();
	ParticleSystemQuad* creategoodnormal();
	ParticleSystemQuad* creategoodnormal2();
	int addCount;
	int GAME_STATUS;
};

#endif

