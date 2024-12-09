#include "ForceGenerator.h"
#include "Particle.h"
#include "PhysicScene.h"

void ForceGenerator::update(double dt)
{
	update(dt,mPs->getParticleList());
}

