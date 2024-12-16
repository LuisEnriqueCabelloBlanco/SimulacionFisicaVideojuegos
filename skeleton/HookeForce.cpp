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
	condS = [this](SolidoRigido* rb) {return l_0 >  (rb->getPose()-hookPoint).magnitude(); };
}

HookeForce::HookeForce(const Vector3& pivotPos, SolidoRigido* asignedParticle, double k, double l):ForceGenerator(nullptr),
particleToAplie(nullptr), k(k), l_0(l), hookPoint(pivotPos),particeRb(asignedParticle)
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
	if(particleToAplie != nullptr)
		particleToAplie->addForce(calculateForce(particleToAplie));

	if (particeRb != nullptr) {
		particeRb->addForce(calculateForce(particeRb));
	}
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

Vector3 HookeForce::calculateForce(SolidoRigido* rig)
{
	Vector3 d = rig->getPose() - hookPoint;

	Vector3 F = -k * (d.magnitude() - l_0) * d.getNormalized();
	return F;
}
