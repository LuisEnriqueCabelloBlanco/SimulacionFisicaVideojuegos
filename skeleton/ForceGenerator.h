#pragma once
#include <list>
#include "Particle.h";

class ForceGenerator
{
public:
	ForceGenerator() {}

	void suscribeParticle(Particle* par);

	void update(double dt);

	void clearParticles();

	virtual Vector3 calculateForce(Particle* par)=0;

protected:
	std::list<Particle*> suscribedParticles;

};

