#include "HookeForce.h"

HookeForce::HookeForce(const Vector3& pivotPos, Particle* asignedParticle, double k, double l) :ForceGenerator(nullptr),
particleToAplie(asignedParticle), k(k), l_0(l),hookPoint(pivotPos)
{
	GeometrySpec geom;
	geom.shape = CUBE;
	geom.box.x = 0.5;
	geom.box.y = 0.5;
	geom.box.z = 0.5;
	reference = new Particle(hookPoint, geom, 0, 0, Color(1, 0, 1, 1));
}

void HookeForce::update(double dt)
{
	particleToAplie->addForce(calculateForce(particleToAplie));
}

HookeForce::~HookeForce()
{
	delete reference;
}

Vector3 HookeForce::calculateForce(Particle* par)
{
	Vector3 d = par->getPos()- hookPoint;

	Vector3 F = -k*(d.magnitude()-l_0)*d.getNormalized();

	return F;
}
