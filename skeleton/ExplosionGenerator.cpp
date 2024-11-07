#include "ExplosionGenerator.h"

Vector3 ExplosionGenerator::calculateForce(Particle* par)
{
	Vector3 force = Vector3(0);
	Vector3 deltaPos = par->getPos() - center;
	float r = deltaPos.magnitude();
	if (r < explosionMaxRange) {
		force = (intensity / pow(r, 2)) * 
			deltaPos * 
			exp(-(time / timeConstant));
	}

    return force;
}
