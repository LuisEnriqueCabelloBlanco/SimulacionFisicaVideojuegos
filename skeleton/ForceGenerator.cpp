#include "ForceGenerator.h"
#include "Particle.h"
void ForceGenerator::suscribeParticle(Particle* par)
{
	suscribedParticles.push_back(par);
}

void ForceGenerator::update(double dt)
{
	for (auto p : suscribedParticles) {
		p->addForce(calculateForce(p));
	}
}

void ForceGenerator::clearParticles()
{

	std::list<std::list<Particle*>::iterator> Pl;
	for (auto p = suscribedParticles.begin(); p != suscribedParticles.end();++p) {
		if (!(*p)->getAlive()) {
			Pl.push_back(p);
		}
	}

	for (auto it : Pl) {
		suscribedParticles.erase(it);
	}

}
