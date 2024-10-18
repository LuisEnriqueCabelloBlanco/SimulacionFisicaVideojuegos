#include "GeneradorParticulas.h"
#include "Particle.h"
void GeneradorParticulas::update(double dt)
{
	currentTime += dt;
	addParticle();
	for (auto p : mParticles) {
		p->integrate(dt);
	}
}

void GeneradorParticulas::addParticle()
{
	if (currentTime > nextSpawnTime) {
		//spawn particle magic

		//randomize particle variables
		
	}
}
