#include "ForceGenerator.h"
#include "Particle.h"

void ForceGenerator::update(double dt)
{
	//for (auto p : suscribedParticles) {
	//	p->addForce(calculateForce(p));
	//}

	for (auto p : mPs->getParticleList()) {
		if (cond(p)) {
			p->addForce(calculateForce(p));
		}
	}
}
