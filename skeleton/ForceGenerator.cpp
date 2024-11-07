#include "ForceGenerator.h"
#include "Particle.h"

void ForceGenerator::update(double dt)
{
	//for (auto p : suscribedParticles) {
	//	p->addForce(calculateForce(p));
	//}
	time += dt;
	for (auto p : mPs->getParticleList()) {
		if (cond(p)) {
			p->addForce(calculateForce(p));
		}
	}
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
