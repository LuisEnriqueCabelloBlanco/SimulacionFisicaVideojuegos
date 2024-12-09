#include "DualHookForce.h"

DualHookForce::DualHookForce(Particle* a, Particle* b, double k, double l):ForceGenerator(nullptr),
	k(k), l_0(l),pA(a),pB(b)
{

}

void DualHookForce::update(double dt)
{
	pA->addForce(calculateSpringForce(pA, pB));
	pB->addForce(calculateSpringForce(pB, pA));
}

Vector3 DualHookForce::calculateForce(Particle* par)
{
    return Vector3();
}

Vector3 DualHookForce::calculateSpringForce(Particle* A, Particle* B)
{
	Vector3 d = A->getPos() - B->getPos();

	Vector3 F = -k * (d.magnitude() - l_0) * d.getNormalized();

	return F;
}

Vector3 DualHookForce::calculateForce(SolidoRigido* rig)
{
	return Vector3();
}
