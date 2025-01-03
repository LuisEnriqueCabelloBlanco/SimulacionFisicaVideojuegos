#include "ExplosionGenerator.h"

ExplosionGenerator::ExplosionGenerator(const Vector3& center, float range, float timeConst, float intensity):
	ForceGenerator(nullptr),center(center),explosionMaxRange(range),timeConstant(timeConst),intensity(intensity)
{
}

Vector3 ExplosionGenerator::calculateForce(Particle* par)
{	
	explosionMaxRange = rangeSpeed * time;
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

Vector3 ExplosionGenerator::calculateForce(SolidoRigido* rig)
{
	explosionMaxRange = rangeSpeed * time;
	Vector3 force = Vector3(0);
	Vector3 deltaPos = rig->getPose() - center;
	float r = deltaPos.magnitude();
	if (r < explosionMaxRange) {
		force = (intensity / pow(r, 2)) *
			deltaPos *
			exp(-(time / timeConstant));
	}

	return force;
}
