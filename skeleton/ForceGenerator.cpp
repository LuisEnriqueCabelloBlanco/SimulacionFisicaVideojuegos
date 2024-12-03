#include "ForceGenerator.h"
#include "Particle.h"
#include "PhysicScene.h"

void ForceGenerator::update(double dt)
{
	update(dt,mPs->getParticleList());
}

void ForceGenerator::update(double dt, const std::list<Particle*>& list)
{
	time += dt; 
	for (auto p : list) {
		if (cond(p)) {
			p->addForce(calculateForce(p));
		}
	}
}
